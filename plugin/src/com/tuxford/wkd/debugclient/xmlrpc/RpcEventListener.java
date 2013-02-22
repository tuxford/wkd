package com.tuxford.wkd.debugclient.xmlrpc;

import java.io.IOException;

import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.server.PropertyHandlerMapping;
import org.apache.xmlrpc.server.XmlRpcServer;
import org.apache.xmlrpc.server.XmlRpcServerConfigImpl;
import org.apache.xmlrpc.webserver.WebServer;

import com.tuxford.wkd.debugclient.ITargetStateEventHandler;
import com.tuxford.wkd.debugclient.xmlrpc.event.OutputEventHandler;
import com.tuxford.wkd.debugclient.xmlrpc.event.TargetStateEventHandler;

public class RpcEventListener extends Thread {

	private WebServer webServer;
	private EventRequestProcessorFactoryFactory requestProcessorFactoryFactory = new EventRequestProcessorFactoryFactory();
	
	public void init(int port) throws Exception {
		
		webServer = new WebServer(port);
		
		XmlRpcServer xmlRpcEventListener = webServer.getXmlRpcServer();
		
		setHandlers(xmlRpcEventListener);
		updateXmlrpcServerConfig((XmlRpcServerConfigImpl) xmlRpcEventListener.getConfig());
	}
		
	public void run() {
		try {
			webServer.start();
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
	}
	
	public void stopListen() {
		webServer.shutdown();
	}
	
	public void setTargetStateEventHandler(ITargetStateEventHandler eventHandler) {
		// TODO Auto-generated method stub
		requestProcessorFactoryFactory.addTargetStateEventHandler(eventHandler);
		
	}

	protected void finalize() {
		stopListen();
	}
	
	private void setHandlers(XmlRpcServer xmlRpcEventListener) throws XmlRpcException {
		PropertyHandlerMapping handlerMapping = new PropertyHandlerMapping();
//FIXME: add good handler setup interface		
		handlerMapping.setRequestProcessorFactoryFactory(requestProcessorFactoryFactory);
		handlerMapping.addHandler("TargetStateEvent", TargetStateEventHandler.class);
		handlerMapping.addHandler("OutputEvent", OutputEventHandler.class);
//		((AbstractReflectiveHandlerMapping) handlerMapping).setVoidMethodEnabled(true);
		xmlRpcEventListener.setHandlerMapping(handlerMapping);
	}
	
	private void updateXmlrpcServerConfig(XmlRpcServerConfigImpl serverConfig) {
		serverConfig.setEnabledForExtensions(true);
		serverConfig.setContentLengthOptional(false);		
	}

}
