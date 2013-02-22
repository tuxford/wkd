package com.tuxford.wkd.debugclient.xmlrpc;

import java.util.Vector;

import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.XmlRpcRequest;
import org.apache.xmlrpc.server.RequestProcessorFactoryFactory;

import com.tuxford.wkd.debugclient.ITargetStateEventHandler;
import com.tuxford.wkd.debugclient.xmlrpc.event.TargetStateEventHandler;

public class EventRequestProcessorFactoryFactory implements RequestProcessorFactoryFactory {

	private RequestProcessorFactory requestProcessorFactory = new EventStateRequestProcessorFactory();
	private Vector<ITargetStateEventHandler> targetStateEventHandlers = new Vector<ITargetStateEventHandler>();
	
	public EventRequestProcessorFactoryFactory() {
		
	}
	
	@Override
	@SuppressWarnings("rawtypes")
	public RequestProcessorFactory getRequestProcessorFactory(Class c)
			throws XmlRpcException {

		return requestProcessorFactory;
	}

	public void addTargetStateEventHandler(ITargetStateEventHandler eventHandler) {
		targetStateEventHandlers.add(eventHandler);
	}

	private class EventStateRequestProcessorFactory implements RequestProcessorFactory {

		@Override
		public Object getRequestProcessor(XmlRpcRequest arg0)
				throws XmlRpcException {
			return new TargetStateEventHandler(targetStateEventHandlers);
		}
		
	}

}
