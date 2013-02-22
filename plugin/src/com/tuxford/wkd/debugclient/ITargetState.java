package com.tuxford.wkd.debugclient;

public interface ITargetState {
	public String getStateId();
	public boolean isCanTerminate();
	public boolean isTerminated();
	public boolean isCanResume();
	public boolean isCanSuspend();
	public boolean isSuspended();
	public boolean isCanDisconnect();
	public boolean isDisconnected();
}
