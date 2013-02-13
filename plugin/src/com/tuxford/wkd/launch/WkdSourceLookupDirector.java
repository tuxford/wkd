package com.tuxford.wkd.launch;

import org.eclipse.debug.core.sourcelookup.AbstractSourceLookupDirector;
import org.eclipse.debug.core.sourcelookup.ISourceLookupParticipant;

public class WkdSourceLookupDirector extends AbstractSourceLookupDirector {

	public void initializeParticipants() {
		addParticipants(new ISourceLookupParticipant[]{new WkdSourceLookupParticipant()});
	}
}
