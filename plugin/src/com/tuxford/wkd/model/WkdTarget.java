package com.tuxford.wkd.model;

import org.eclipse.core.resources.IMarkerDelta;
import org.eclipse.core.runtime.PlatformObject;
import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IBreakpoint;
import org.eclipse.debug.core.model.IDebugElement;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.IMemoryBlock;
import org.eclipse.debug.core.model.IProcess;
import org.eclipse.debug.core.model.IThread;

import com.tuxford.wkd.debugclient.IDebugClient;
import com.tuxford.wkd.debugclient.ITargetState;
import com.tuxford.wkd.debugclient.ITargetStateEventHandler;

public class WkdTarget extends PlatformObject implements IDebugTarget {

	private static final String TARGET_NAME = "com.tuxford.wkd";
	public static final String ID_WKD_DEBUG_MODEL = "com.tuxford.wkd.id";
	private ILaunch launch;
	private IDebugClient debugClient;
	private IThread[] threads = new IThread[]{};
	private ITargetState targetState;
	
	public WkdTarget(ILaunch launch, IDebugClient debugClient) throws Exception {
		this.launch = launch;
		this.debugClient = debugClient;
		this.targetState = debugClient.getTargetState();
		debugClient.setTargetStateEventHandler(new ITargetStateEventHandler() {
			
			@Override
			public void onEvent(ITargetState newTargetState) {
				onChangeState(newTargetState);
			}
		});
		
		debugClient.connect();
	}
	
	@Override
	public IDebugTarget getDebugTarget() {
		return this;
	}

	@Override
	public ILaunch getLaunch() {
		return launch;
	}

	@Override
	public String getModelIdentifier() {
		return ID_WKD_DEBUG_MODEL;
	}

	@Override
	@SuppressWarnings("rawtypes")
	public Object getAdapter(Class adapter) {
		if (adapter == IDebugElement.class) {
			return this;
		}
		return super.getAdapter(adapter);
	}

	@Override
	public boolean canTerminate() {
		try {
			return targetState.isCanTerminate();
		} catch (Exception e) {
			System.out.println("Connection with target lost." + e.getMessage());
			return false;
		}
	}

	@Override
	public boolean isTerminated() {
		try {
			return targetState.isTerminated();
		} catch (Exception e) {
			System.out.println("Connection with target lost." + e.getMessage());
			return false;
		}
	}

	@Override
	public void terminate() throws DebugException {
		// TODO Auto-generated method stub
		System.out.println("WkdTarget::terminate()");
	}

	@Override
	public boolean canResume() {
		try {
			return targetState.isCanResume();
		} catch (Exception e) {
			System.out.println("Connection with target lost." + e.getMessage());
			return false;
		}
	}

	@Override
	public boolean canSuspend() {
		try {
			return targetState.isCanResume();
		} catch (Exception e) {
			System.out.println("Connection with target lost." + e.getMessage());
			return false;
		}
	}

	@Override
	public boolean isSuspended() {
		try {
			return targetState.isSuspended();
		} catch (Exception e) {
			System.out.println("Connection with target lost." + e.getMessage());
			return false;
		}
	}

	@Override
	public void resume() throws DebugException {
		// TODO Auto-generated method stub
		System.out.println("WkdTarget::resume()");
	}

	@Override
	public void suspend() throws DebugException {
		// TODO Auto-generated method stub
		System.out.println("WkdTarget::suspend()");
	}

	@Override
	public void breakpointAdded(IBreakpoint arg0) {
		// TODO Auto-generated method stub
		System.out.println("WkdTarget::breakpointAdded()");
	}

	@Override
	public void breakpointChanged(IBreakpoint arg0, IMarkerDelta arg1) {
		// TODO Auto-generated method stub
		System.out.println("WkdTarget::breakpointChanged()");
	}

	@Override
	public void breakpointRemoved(IBreakpoint arg0, IMarkerDelta arg1) {
		// TODO Auto-generated method stub
		System.out.println("WkdTarget::breakpointRemoved()");
	}

	@Override
	public boolean canDisconnect() {
		try {
			return targetState.isCanDisconnect();
		} catch (Exception e) {
			System.out.println("Connection with target lost." + e.getMessage());
			return false;
		}
	}

	@Override
	public void disconnect() throws DebugException {
		// TODO Auto-generated method stub
		System.out.println("WkdTarget::disconnect()");
	}

	@Override
	public boolean isDisconnected() {
		try {
			return targetState.isDisconnected();
		} catch (Exception e) {
			System.out.println("Connection with target lost." + e.getMessage());
			return false;
		}
	}

	@Override
	public IMemoryBlock getMemoryBlock(long arg0, long arg1)
			throws DebugException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean supportsStorageRetrieval() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public String getName() throws DebugException {
		return TARGET_NAME;
	}

	@Override
	public IProcess getProcess() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public IThread[] getThreads() throws DebugException {
		return threads;
	}

	@Override
	public boolean hasThreads() throws DebugException {
		return false;
	}

	@Override
	public boolean supportsBreakpoint(IBreakpoint arg0) {
		// TODO Auto-generated method stub
		return true;
	}

	private void onChangeState(ITargetState newTargetState) {
		targetState = newTargetState;
		
		if (targetState.getStateId().equals(BasicTargetStates.CONNECTED)) {
			try {
				debugClient.attachKernel("1394:channel=11");
				System.out.println("Attach : ");
			}
			catch (Exception e) {
				System.out.println("Attach failed: " + e.getMessage());
//TODO: add attach kernel error handling				
			}
		}		
		else if (targetState.getStateId().equals(BasicTargetStates.ATTACHED_KERNEL)) {
			try {
//TODO: parameters must be took from launch configuration
				int setSourcePathResult = debugClient.setSourcePath("E:\\runtime-New_configuration\\sources_kmd\\");
				if (setSourcePathResult != 0) {
					System.out.print("Set source path failed: ");
					System.out.print(setSourcePathResult);
					System.out.println();
				}
			} catch (Exception e) {
				// TODO Auto-generated catch block
				System.out.println("Set source path failed with exception: " + e.getMessage());
			}
		}
	}
}
