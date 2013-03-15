package com.tuxford.wkd.debugclient.xmlrpc;

import java.net.URL;

import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;
import com.tuxford.wkd.debugclient.IDebugClient;
import com.tuxford.wkd.debugclient.ITargetState;
import com.tuxford.wkd.debugclient.ITargetStateEventHandler;

public class RpcDebugClient implements IDebugClient {

	private static final String KD_CONNECT_METHOD_ID = "Kd.connect";
	private static final String KD_DISCONNECT_METHOD_ID = "Kd.disconnect";
	private static final String KD_ATTACH_KERNEL_METHOD_ID = "Kd.attachKernel";
	private static final String KD_SET_SYMBOL_PATH_ID = "Kd.setSymbolFilePath";
	private static final String KD_SET_SOURCE_PATH_ID = "Kd.setSourcePath";
	private static final String KD_SET_DRIVER_REPLACEMENT_MAP_ID = "Kd.setDriverReplacementMap";
	
	private XmlRpcClientConfigImpl clientConfig = new XmlRpcClientConfigImpl();
	private XmlRpcClient xmlrpcClient = new XmlRpcClient();
	private RpcEventListener rpcEventListener;
	private RpcTargetState rpcTargetState = RpcTargetState.getNoTargetState();

	@Override
	public int connect() throws Exception {
		Object params[] = {};
		Integer result = (Integer)xmlrpcClient.execute(KD_CONNECT_METHOD_ID, params);
		
		return result.intValue();
	}
	
	@Override
	public int disconnect() throws Exception {
		Object params[] = {};
		Integer result = (Integer)xmlrpcClient.execute(KD_DISCONNECT_METHOD_ID, params);
		
		return result.intValue();
	}

	@Override
	public int attachKernel(String attachParams) throws Exception {
		Object params[] = {attachParams};
		Integer result = (Integer)xmlrpcClient.execute(KD_ATTACH_KERNEL_METHOD_ID, params);
		
		System.out.println(result.toString());
		return result.intValue();
	}

	@Override
	public int setSymbolFilePath(String symbolPath) throws Exception {
		Object params[] = {symbolPath};
		Integer result = (Integer)xmlrpcClient.execute(KD_SET_SYMBOL_PATH_ID, params);
		
		System.out.println(result.toString());
		return result.intValue();
	}
	
	@Override
	public int setSourcePath(String sourcePath) throws Exception {
		Object params[] = {sourcePath};
		Integer result = (Integer)xmlrpcClient.execute(KD_SET_SOURCE_PATH_ID, params);
		
		System.out.println(result.toString());
		return result.intValue();
	}

	public int setDriverReplacementMap(String oldDriver, String newDriver) throws Exception {
		Object params[] = {oldDriver, newDriver};
		Integer result = (Integer)xmlrpcClient.execute(KD_SET_DRIVER_REPLACEMENT_MAP_ID, params);
		
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
