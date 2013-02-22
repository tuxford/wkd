package com.tuxford.wkd.debugclient;

public interface IDebugClient {
	public int connect() throws Exception;
	public int attachKernel(String attachParams) throws Exception;
	public ITargetState getTargetState();
	public void setTargetStateEventHandler(ITargetStateEventHandler eventHandler);
}
