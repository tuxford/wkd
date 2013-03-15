package com.tuxford.wkd.debugclient;

public interface IDebugClient {
	public int connect() throws Exception;
	public int disconnect() throws Exception;
	public int attachKernel(String attachParams) throws Exception;
	public ITargetState getTargetState();
	public int setSymbolFilePath(String symbolPath) throws Exception;
	public int setSourcePath(String sourcePath) throws Exception;
	public int setDriverReplacementMap(String oldDriver, String newDriver) throws Exception;
	public void setTargetStateEventHandler(ITargetStateEventHandler eventHandler);
}
