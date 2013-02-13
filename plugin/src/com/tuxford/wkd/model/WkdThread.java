package com.tuxford.wkd.model;

import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.model.IBreakpoint;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IThread;

public class WkdThread extends WkdDebugElement implements IThread {
	
	private IBreakpoint[] fBreakpoints;
	
	private boolean fStepping = false;
	
	public WkdThread(WkdDebugTarget target) {
		super(target);
	}
	
	public IStackFrame[] getStackFrames() throws DebugException {
		if (isSuspended()) {
			return ((WkdDebugTarget)getDebugTarget()).getStackFrames();
		} else {
			return new IStackFrame[0];
		}
	}

	public boolean hasStackFrames() throws DebugException {
		return isSuspended();
	}
	
	public int getPriority() throws DebugException {
		return 0;
	}
	
	public IStackFrame getTopStackFrame() throws DebugException {
		IStackFrame[] frames = getStackFrames();
		if (frames.length > 0) {
			return frames[0];
		}
		return null;
	}
	
	public String getName() throws DebugException {
		return "Thread[1]";
	}
	
	public IBreakpoint[] getBreakpoints() {
		if (fBreakpoints == null) {
			return new IBreakpoint[0];
		}
		return fBreakpoints;
	}
	
	protected void setBreakpoints(IBreakpoint[] breakpoints) {
		fBreakpoints = breakpoints;
	}
	
	public boolean canResume() {
		return isSuspended();
	}
	
	public boolean canSuspend() {
		return !isSuspended();
	}
	
	public boolean isSuspended() {
		return getDebugTarget().isSuspended();
	}
	
	public void resume() throws DebugException {
		getDebugTarget().resume();
	}
	
	public void suspend() throws DebugException {
		getDebugTarget().suspend();
	}
	
	public boolean canStepInto() {
		return false;
	}
	
	public boolean canStepOver() {
		return isSuspended();
	}
	
	public boolean canStepReturn() {
		return false;
	}
	
	public boolean isStepping() {
		return fStepping;
	}
	
	public void stepInto() throws DebugException {
	}
	
	public void stepOver() throws DebugException {
		((WkdDebugTarget)getDebugTarget()).step();
	}
	
	public void stepReturn() throws DebugException {
	}
	
	public boolean canTerminate() {
		return !isTerminated();
	}
	
	public boolean isTerminated() {
		return getDebugTarget().isTerminated();
	}
	
	public void terminate() throws DebugException {
		getDebugTarget().terminate();
	}
	
	protected void setStepping(boolean stepping) {
		fStepping = stepping;
	}
}
