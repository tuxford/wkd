package com.tuxford.wkd.debugclient.xmlrpc;

import java.net.URL;

import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;
import com.tuxford.wkd.debugclient.IDebugClient;
import com.tuxford.wkd.debugclient.ITargetState;
import com.tuxford.wkd.debugclient.ITargetStateEventHandler;

public class RpcDebugClient implements IDebugClient {

	private static final String KD_CONNECT_METHOD_ID = "Kd.connect";
	private static final String KD_ATTACH_KERNEL_METHOD_ID = "Kd.attachKernel";
	
	private XmlRpcClientConfigImpl clientConfig = new XmlRpcClientConfigImpl();
	private XmlRpcClient xmlrpcClient = new XmlRpcClient();
	private RpcEventListener rpcEventListener;
	private RpcTargetState rpcTargetState = RpcTargetState.getNoTargetState();

	public int connect() throws Exception {
		Object params[] = {};
		Integer result = (Integer)xmlrpcClient.execute(KD_CONNECT_METHOD_ID, params);
		
		return result.intValue();
	}

	@Override
	public int attachKernel(String attachParams) throws Exception {
		Object params[] = {attachParams};
		Integer result = (Integer)xmlrpcClient.execute(KD_ATTACH_KERNEL_METHOD_ID, params);
		
		System.out.println(result.toString());
		return result.intValue();
	}


	public ITargetState getTargetState() {
		return rpcTargetState;
	}
	
	public void init(String serverUrl, String user, String password, int eventPortListener) throws Exception {
			initEventListener(eventPortListener);
			
			clientConfig.setServerURL(new URL(serverUrl));
			clientConfig.setBasicUserName(user);
			clientConfig.setBasicPassword(password);
			xmlrpcClient.setConfig(clientConfig);			
	}
	
	public void setTargetStateEventHandler(ITargetStateEventHandler eventHandler) {
		rpcEventListener.setTargetStateEventHandler(eventHandler);
	}
	
	private void initEventListener(int port) throws Exception {
		rpcEventListener = new RpcEventListener();
		rpcEventListener.init(port);
		rpcEventListener.start();
	}

}
