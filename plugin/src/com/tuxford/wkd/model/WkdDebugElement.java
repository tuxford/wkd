package com.tuxford.wkd.model;

import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.PlatformObject;
import org.eclipse.core.runtime.Status;
import org.eclipse.debug.core.DebugEvent;
import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IDebugElement;
import org.eclipse.debug.core.model.IDebugTarget;

import com.tuxford.wkd.Activator;
import com.tuxford.wkd.launch.cfg.IWkdConstants;

public abstract class WkdDebugElement extends PlatformObject implements IDebugElement {
	
	protected WkdDebugTarget kdTarget;
	
	public WkdDebugElement(WkdDebugTarget target) {
		kdTarget = target;
	}
	
	public String getModelIdentifier() {
		return IWkdConstants.ID_PDA_DEBUG_MODEL;
	}

	public IDebugTarget getDebugTarget() {
		return kdTarget;
	}

	public ILaunch getLaunch() {
		return getDebugTarget().getLaunch();
	}

	@SuppressWarnings("rawtypes")
	public Object getAdapter(Class adapter) {
		if (adapter == IDebugElement.class) {
			return this;
		}
		return super.getAdapter(adapter);
	}
	
	protected void abort(String message, Throwable e) throws DebugException {
		throw new DebugException(new Status(IStatus.ERROR, Activator.PLUGIN_ID, 
				DebugPlugin.INTERNAL_ERROR, message, e));
	}
	
	protected void fireEvent(DebugEvent event) {
		DebugPlugin.getDefault().fireDebugEventSet(new DebugEvent[] {event});
	}
	
	protected void fireCreationEvent() {
		fireEvent(new DebugEvent(this, DebugEvent.CREATE));
	}	
	
	public void fireResumeEvent(int detail) {
		fireEvent(new DebugEvent(this, DebugEvent.RESUME, detail));
	}

	public void fireSuspendEvent(int detail) {
		fireEvent(new DebugEvent(this, DebugEvent.SUSPEND, detail));
	}
	
	protected void fireTerminateEvent() {
		fireEvent(new DebugEvent(this, DebugEvent.TERMINATE));
	}	
}
