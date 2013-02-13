package com.tuxford.wkd.launch;

import org.eclipse.core.runtime.CoreException;
import org.eclipse.debug.core.sourcelookup.AbstractSourceLookupParticipant;

import com.tuxford.wkd.model.WkdStackFrame;

public class WkdSourceLookupParticipant extends AbstractSourceLookupParticipant {

	public String getSourceName(Object object) throws CoreException {
		if (object instanceof WkdStackFrame) {
			return ((WkdStackFrame)object).getSourceName();
		}
		return null;
	}
}
