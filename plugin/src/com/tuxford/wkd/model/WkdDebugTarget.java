package com.tuxford.wkd.model;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.text.MessageFormat;

import org.eclipse.core.resources.IMarker;
import org.eclipse.core.resources.IMarkerDelta;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.Status;
import org.eclipse.core.runtime.jobs.Job;
import org.eclipse.debug.core.DebugEvent;
import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IBreakpoint;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.ILineBreakpoint;
import org.eclipse.debug.core.model.IMemoryBlock;
import org.eclipse.debug.core.model.IProcess;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IThread;
import org.eclipse.debug.core.model.IValue;

import com.tuxford.wkd.launch.cfg.IWkdConstants;

public class WkdDebugTarget extends WkdDebugElement implements IDebugTarget {
	
	private static final String TARGET_NAME = "com.tuxford.wkd";

	private IProcess kdProcess;
	private ILaunch kdLaunch;
	
	
	// sockets to communicate with VM
	private Socket fRequestSocket;
	private PrintWriter requestWriter;
	private BufferedReader requestReader;
	private Socket fEventSocket;
	private BufferedReader eventReader;
	
	// suspend state
	private boolean fSuspended = true;
	
	// terminated state
//	private boolean fTerminated = false;
	
	// threads
	private WkdThread wkdThread;
	private IThread[] threads;
	
	// event dispatch job
	private EventDispatchJob fEventDispatch;
	private InputStream kdInputStream;
	private OutputStream kdOutputStream;
	private InputStream kdErrorStream;
	
	class EventDispatchJob extends Job {
		
		public EventDispatchJob() {
			super("PDA Event Dispatch");
			setSystem(true);
		}

		protected IStatus run(IProgressMonitor monitor) {
			String event = "";
			while (!isTerminated() && event != null) {
				try {
					event = eventReader.readLine();
					if (event != null) {
						wkdThread.setBreakpoints(null);
						wkdThread.setStepping(false);
						if (event.equals("started")) {
							started();
						} else if (event.equals("terminated")) {
							terminated();
						} else if (event.startsWith("resumed")) {
							if (event.endsWith("step")) {
								wkdThread.setStepping(true);
								resumed(DebugEvent.STEP_OVER);
							} else if (event.endsWith("client")) {
								resumed(DebugEvent.CLIENT_REQUEST);
							}
						} else if (event.startsWith("suspended")) {
							if (event.endsWith("client")) {
								suspended(DebugEvent.CLIENT_REQUEST);
							} else if (event.endsWith("step")) {
								suspended(DebugEvent.STEP_END);
							} else if (event.indexOf("breakpoint") >= 0) {
								breakpointHit(event);
							}
						}
					}
				} catch (IOException e) {
					terminated();
				}
			}
			return Status.OK_STATUS;
		}
		
	}
	
	public WkdDebugTarget(ILaunch kdLaunch, IProcess kdProcess, InputStream kdInputStream, OutputStream kdOutputStream, InputStream kdErrorStream) throws CoreException {
		super(null);
		
		this.kdLaunch = kdLaunch;
		this.kdTarget = this;
		this.kdProcess = kdProcess;
		this.kdInputStream = kdInputStream;
		this.kdOutputStream = kdOutputStream;
		this.kdErrorStream = kdErrorStream;
		
		requestWriter = new PrintWriter(kdOutputStream);
		requestReader = new BufferedReader(new InputStreamReader(kdInputStream));
//			eventReader = new BufferedReader(new InputStreamReader(fEventSocket.getInputStream()));
			

		wkdThread = new WkdThread(this);
		threads = new IThread[] {wkdThread};
		fEventDispatch = new EventDispatchJob();
		fEventDispatch.schedule();
		
		DebugPlugin.getDefault().getBreakpointManager().addBreakpointListener(this);
	}
	
	public IProcess getProcess() {
		return kdProcess;
	}
	
	public IThread[] getThreads() throws DebugException {
		return threads;
	}
	
	public boolean hasThreads() throws DebugException {
		boolean hasThreads = false;
		for (IThread thread : threads) {
			if (thread.isTerminated() == false) {
				hasThreads = true;
				break;
			} 
		}
		return hasThreads; 
	}
	
	public String getName() {
		return TARGET_NAME;
	}
	
	public boolean supportsBreakpoint(IBreakpoint breakpoint) {
		if (breakpoint.getModelIdentifier().equals(IWkdConstants.ID_PDA_DEBUG_MODEL)) {
			String program = TARGET_NAME;
			if (program != null) {
				IMarker marker = breakpoint.getMarker();
				if (marker != null) {
					IPath p = new Path(program);
					return marker.getResource().getFullPath().equals(p);
				}
			}
		}
		return false;
	}
	
	public IDebugTarget getDebugTarget() {
		return this;
	}
	
	public ILaunch getLaunch() {
		return kdLaunch;
	}
	
	public boolean canTerminate() {
		return getProcess().canTerminate();
	}
	
	public boolean isTerminated() {
		return getProcess().isTerminated();
	}
	
	public void terminate() throws DebugException {
		synchronized (fRequestSocket) {
			requestWriter.println("exit");
			requestWriter.flush();
		}		
	}
	
	public boolean canResume() {
		return !isTerminated() && isSuspended();
	}
	
	public boolean canSuspend() {
		return !isTerminated() && !isSuspended();
	}
	
	public boolean isSuspended() {
		return fSuspended;
	}
	
	public void resume() throws DebugException {
		sendRequest("resume");
	}
	
	private void resumed(int detail) {
		fSuspended = false;
		wkdThread.fireResumeEvent(detail);
	}
	
	private void suspended(int detail) {
		fSuspended = true;
		wkdThread.fireSuspendEvent(detail);
	}	
	
	public void suspend() throws DebugException {
	}
	
	public void breakpointAdded(IBreakpoint breakpoint) {
		if (supportsBreakpoint(breakpoint)) {
			try {
				if (breakpoint.isEnabled()) {
					try {
						sendRequest("set " + (((ILineBreakpoint)breakpoint).getLineNumber() - 1));
					} catch (CoreException e) {
					}
				}
			} catch (CoreException e) {
			}
		}
	}
	
	public void breakpointRemoved(IBreakpoint breakpoint, IMarkerDelta delta) {
		if (supportsBreakpoint(breakpoint)) {
			try {
				sendRequest("clear " + ((ILineBreakpoint)breakpoint).getLineNumber());
			} catch (CoreException e) {
			}
		}
	}
	
	public void breakpointChanged(IBreakpoint breakpoint, IMarkerDelta delta) {
		if (supportsBreakpoint(breakpoint)) {
			try {
				if (breakpoint.isEnabled()) {
					breakpointAdded(breakpoint);
				} else {
					breakpointRemoved(breakpoint, null);
				}
			} catch (CoreException e) {
			}
		}
	}
	
	public boolean canDisconnect() {
		return false;
	}
	
	public void disconnect() throws DebugException {
	}
	
	public boolean isDisconnected() {
		return false;
	}
 
	public boolean supportsStorageRetrieval() {
		return false;
	}
	public IMemoryBlock getMemoryBlock(long startAddress, long length) throws DebugException {
		return null;
	}

	private void started() {
		fireCreationEvent();
		installDeferredBreakpoints();
		try {
			resume();
		} catch (DebugException e) {
		}
	}
	
	private void installDeferredBreakpoints() {
		IBreakpoint[] breakpoints = DebugPlugin.getDefault().getBreakpointManager().getBreakpoints(IWkdConstants.ID_PDA_DEBUG_MODEL);
		for (int i = 0; i < breakpoints.length; i++) {
			breakpointAdded(breakpoints[i]);
		}
	}
	
	private void terminated() {
//		fTerminated = true; is it need?
		fSuspended = false;
		DebugPlugin.getDefault().getBreakpointManager().removeBreakpointListener(this);
		fireTerminateEvent();
	}
	
	protected IStackFrame[] getStackFrames() throws DebugException {
		synchronized (fRequestSocket) {
			requestWriter.println("stack");
			requestWriter.flush();
			try {
				String framesData = requestReader.readLine();
				if (framesData != null) {
					String[] frames = framesData.split("#");
					IStackFrame[] theFrames = new IStackFrame[frames.length];
					for (int i = 0; i < frames.length; i++) {
						String data = frames[i];
						theFrames[frames.length - i - 1] = new WkdStackFrame(wkdThread, data, i);
					}
					return theFrames;
				}
			} catch (IOException e) {
				abort("Unable to retrieve stack frames", e);
			}
		}
		return new IStackFrame[0];
	}
	
	protected void step() throws DebugException {
		sendRequest("step");
	}
	
	protected IValue getVariableValue(WkdVariable variable) throws DebugException {
		synchronized (fRequestSocket) {
			requestWriter.println("var " + variable.getStackFrame().getIdentifier() + " " + variable.getName());
			requestWriter.flush();
			try {
				String value = requestReader.readLine();
				return new WkdValue(this, value);
			} catch (IOException e) {
				abort(
						MessageFormat.format("Unable to retrieve value for variable {0}", (Object)new String[]{variable.getName()}), e);
			}
		}
		return null;
	}
	
	public IValue[] getDataStack() throws DebugException {
		synchronized (fRequestSocket) {
			requestWriter.println("data");
			requestWriter.flush();
			try {
				String valueString = requestReader.readLine();
				if (valueString != null && valueString.length() > 0) {
					String[] values = valueString.split("\\|");
					IValue[] theValues = new IValue[values.length];
					for (int i = 0; i < values.length; i++) {
						String value = values[values.length - i - 1];
						theValues[i] = new WkdValue(this, value);
					}
					return theValues;
				}
			} catch (IOException e) {
				abort("Unable to retrieve data stack", e);
			}
		}
		return new IValue[0];		
	}
	
	private void sendRequest(String request) throws DebugException {
		synchronized (fRequestSocket) {
			requestWriter.println(request);
			requestWriter.flush();
			try {
				// wait for "ok"
				String response = requestReader.readLine();
				System.out.println(response);
			} catch (IOException e) {
				abort("Request failed: " + request, e);
			}
		}		
	}
	
	private void breakpointHit(String event) {
		// determine which breakpoint was hit, and set the thread's breakpoint
		int lastSpace = event.lastIndexOf(' ');
		if (lastSpace > 0) {
			String line = event.substring(lastSpace + 1);
			int lineNumber = Integer.parseInt(line);
			IBreakpoint[] breakpoints = DebugPlugin.getDefault().getBreakpointManager().getBreakpoints(IWkdConstants.ID_PDA_DEBUG_MODEL);
			for (int i = 0; i < breakpoints.length; i++) {
				IBreakpoint breakpoint = breakpoints[i];
				if (supportsBreakpoint(breakpoint)) {
					if (breakpoint instanceof ILineBreakpoint) {
						ILineBreakpoint lineBreakpoint = (ILineBreakpoint) breakpoint;
						try {
							if (lineBreakpoint.getLineNumber() == lineNumber) {
								wkdThread.setBreakpoints(new IBreakpoint[]{breakpoint});
								break;
							}
						} catch (CoreException e) {
						}
					}
				}
			}
		}
		suspended(DebugEvent.BREAKPOINT);
	}	
}
