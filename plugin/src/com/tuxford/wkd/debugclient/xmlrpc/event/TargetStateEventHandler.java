package com.tuxford.wkd.debugclient.xmlrpc.event;

import java.util.Vector;

import com.tuxford.wkd.debugclient.ITargetStateEventHandler;

public class TargetStateEventHandler {

	private Vector<ITargetStateEventHandler> targetStateEventHandlers;

	public TargetStateEventHandler(
			Vector<ITargetStateEventHandler> targetStateEventHandlers) {
		this.targetStateEventHandlers = targetStateEventHandlers;
	}

	public int onEvent(String eventMessage) {
		for (ITargetStateEventHandler targetStateEventHandler : targetStateEventHandlers) {
			targetStateEventHandler.onEvent(EventDataDeserializer.deserializeTargetState(eventMessage));
		}
		
		System.out.println(eventMessage);
		return 0;
	}

}
