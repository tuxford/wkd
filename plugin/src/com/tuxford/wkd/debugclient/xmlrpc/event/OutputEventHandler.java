package com.tuxford.wkd.debugclient.xmlrpc.event;

public class OutputEventHandler {
	
	public int onEvent(String eventMessage) {
		System.out.print(eventMessage);
		return 0;
	}

}
