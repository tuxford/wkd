package com.tuxford.wkd.model;

import org.eclipse.core.runtime.Path;
import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.model.IRegisterGroup;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IThread;
import org.eclipse.debug.core.model.IVariable;

public class WkdStackFrame extends WkdDebugElement implements IStackFrame {
	
	private WkdThread fThread;
	private String fName;
	private int fPC;
	private String fFileName;
	private int fId;
	private IVariable[] fVariables;
	
	public WkdStackFrame(WkdThread thread, String data, int id) {
		super((WkdDebugTarget) thread.getDebugTarget());
		fId = id;
		fThread = thread;
		init(data);
	}
	
	private void init(String data) {
		String[] strings = data.split("\\|");
		String fileName = strings[0];
		fFileName = (new Path(fileName)).lastSegment();
		String pc = strings[1];
		fPC = Integer.parseInt(pc) + 1;
		fName = strings[2];
		int numVars = strings.length - 3;
		fVariables = new IVariable[numVars];
		for (int i = 0; i < numVars; i++) {
			fVariables[i] = new WkdVariable(this, strings[i + 3]);
		}
	}
	
	public IThread getThread() {
		return fThread;
	}
	
	public IVariable[] getVariables() throws DebugException {
		return fVariables;
	}
	
	public boolean hasVariables() throws DebugException {
		return fVariables.length > 0;
	}
	
	public int getLineNumber() throws DebugException {
		return fPC;
	}
	
	public int getCharStart() throws DebugException {
		return -1;
	}
	
	public int getCharEnd() throws DebugException {
		return -1;
	}
	
	public String getName() throws DebugException {
		return fName;
	}
	
	public IRegisterGroup[] getRegisterGroups() throws DebugException {
		return null;
	}
	
	public boolean hasRegisterGroups() throws DebugException {
		return false;
	}
	
	public boolean canStepInto() {
		return getThread().canStepInto();
	}
	
	public boolean canStepOver() {
		return getThread().canStepOver();
	}
	
	public boolean canStepReturn() {
		return getThread().canStepReturn();
	}
	
	public boolean isStepping() {
		return getThread().isStepping();
	}
	
	public void stepInto() throws DebugException {
		getThread().stepInto();
	}
	
	public void stepOver() throws DebugException {
		getThread().stepOver();
	}
	
	public void stepReturn() throws DebugException {
		getThread().stepReturn();
	}
	
	public boolean canResume() {
		return getThread().canResume();
	}
	
	public boolean canSuspend() {
		return getThread().canSuspend();
	}
	
	public boolean isSuspended() {
		return getThread().isSuspended();
	}
	
	public void resume() throws DebugException {
		getThread().resume();
	}
	
	public void suspend() throws DebugException {
		getThread().suspend();
	}
	
	public boolean canTerminate() {
		return getThread().canTerminate();
	}
	
	public boolean isTerminated() {
		return getThread().isTerminated();
	}
	
	public void terminate() throws DebugException {
		getThread().terminate();
	}
	
	public String getSourceName() {
		return fFileName;
	}

	public boolean equals(Object obj) {
		if (obj instanceof WkdStackFrame) {
			WkdStackFrame sf = (WkdStackFrame)obj;
			try {
				return sf.getSourceName().equals(getSourceName()) &&
					sf.getLineNumber() == getLineNumber() &&
					sf.fId == fId;
			} catch (DebugException e) {
			}
		}
		return false;
	}

	public int hashCode() {
		return getSourceName().hashCode() + fId;
	}
	
	protected int getIdentifier() {
		return fId;
	}
}
