package com.tuxford.wkd.debugclient.xmlrpc;

import com.tuxford.wkd.debugclient.ITargetState;

public class RpcTargetState implements ITargetState {
	private String stateId;
	private boolean canTerminate;
	private boolean terminated;
	private boolean canResume;
	private boolean canSuspend;
	private boolean suspended;
	private boolean canDisconnect;
	private boolean disconnected;
	
	public RpcTargetState() {
	}

	public static RpcTargetState getNoTargetState() {
		RpcTargetState result = new RpcTargetState();
		
		result.setStateId("NoTarget");
		result.setCanDisconnect(false);
		result.setCanResume(false);
		result.setCanSuspend(false);
		result.setCanTerminate(false);
		result.setDisconnected(true);
		result.setSuspended(false);
		result.setTerminated(true);
		
		return result;
	}
	
	public String getStateId() {
		return stateId;
	}
	
	public boolean isCanTerminate() {
		return canTerminate;
	}

	public boolean isTerminated() {
		return terminated;
	}

	public boolean isCanResume() {
		return canResume;
	}

	public boolean isCanSuspend() {
		return canSuspend;
	}

	public boolean isSuspended() {
		return suspended;
	}

	public boolean isCanDisconnect() {
		return canDisconnect;
	}

	public boolean isDisconnected() {
		return disconnected;
	}

	public void setStateId(String stateId) {
		this.stateId = stateId;
	}
	
	public void setCanTerminate(boolean canTerminate) {
		this.canTerminate = canTerminate;
	}

	public void setTerminated(boolean terminated) {
		this.terminated = terminated;
	}

	public void setCanResume(boolean canResume) {
		this.canResume = canResume;
	}

	public void setCanSuspend(boolean canSuspend) {
		this.canSuspend = canSuspend;
	}

	public void setSuspended(boolean suspended) {
		this.suspended = suspended;
	}

	public void setCanDisconnect(boolean canDisconnect) {
		this.canDisconnect = canDisconnect;
	}

	public void setDisconnected(boolean disconnected) {
		this.disconnected = disconnected;
	}
}
