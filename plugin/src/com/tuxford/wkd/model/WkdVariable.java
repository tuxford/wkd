package com.tuxford.wkd.model;

import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.model.IValue;
import org.eclipse.debug.core.model.IVariable;

public class WkdVariable extends WkdDebugElement implements IVariable {
	
	private String fName;
	private WkdStackFrame fFrame;
	
	public WkdVariable(WkdStackFrame frame, String name) {
		super((WkdDebugTarget) frame.getDebugTarget());
		fFrame = frame;
		fName = name;
	}

	public IValue getValue() throws DebugException {
		return ((WkdDebugTarget)getDebugTarget()).getVariableValue(this);
	}

	public String getName() throws DebugException {
		return fName;
	}

	public String getReferenceTypeName() throws DebugException {
		return "Thing";
	}

	public boolean hasValueChanged() throws DebugException {
		return false;
	}

	public void setValue(String expression) throws DebugException {
	}

	public void setValue(IValue value) throws DebugException {
	}

	public boolean supportsValueModification() {
		return false;
	}

	public boolean verifyValue(String expression) throws DebugException {
		return false;
	}

	public boolean verifyValue(IValue value) throws DebugException {
		return false;
	}
	
	protected WkdStackFrame getStackFrame() {
		return fFrame;
	}

}
