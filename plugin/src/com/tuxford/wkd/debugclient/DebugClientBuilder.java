package com.tuxford.wkd.debugclient;

import com.tuxford.wkd.debugclient.xmlrpc.RpcDebugClient;

public class DebugClientBuilder {
	
//TODO: in feature serverUrl and EVENT_LISTENER_PORT should be moved to configuration
	private static final String SERVER_URL = "http://localhost:21605/RPC2";
	private static final int EVENT_LISTENER_PORT = 21606;
	
	public static IDebugClient build() throws Exception {
		
		RpcDebugClient debugClient = new RpcDebugClient();
		debugClient.init(SERVER_URL, "user", "password", EVENT_LISTENER_PORT);
		return debugClient;
	}
}
