package com.tuxford.wkd.model;

import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.model.IValue;
import org.eclipse.debug.core.model.IVariable;

public class WkdValue extends WkdDebugElement implements IValue {
	
	private String fValue;
	
	public WkdValue(WkdDebugTarget target, String value) {
		super(target);
		fValue = value;
	}
	
	public String getReferenceTypeName() throws DebugException {
		try {
			Integer.parseInt(fValue);
		} catch (NumberFormatException e) {
			return "text";
		}
		return "integer";
	}

	public String getValueString() throws DebugException {
		return fValue;
	}

	public boolean isAllocated() throws DebugException {
		return true;
	}

	public IVariable[] getVariables() throws DebugException {
		return new IVariable[0];
	}

	public boolean hasVariables() throws DebugException {
		return false;
	}
}
