package com.tuxford.wkd.ui.pda.model;

import org.eclipse.core.resources.IResource;
import org.eclipse.core.runtime.IAdapterFactory;
import org.eclipse.debug.ui.actions.IToggleBreakpointsTarget;
import org.eclipse.ui.texteditor.ITextEditor;

public class WkdBreakpointAdapterFactory implements IAdapterFactory {

	@SuppressWarnings("rawtypes")
	public Object getAdapter(Object adaptableObject, Class adapterType) {
		if (adaptableObject instanceof ITextEditor) {
			ITextEditor editorPart = (ITextEditor) adaptableObject;
			IResource resource = (IResource) editorPart.getEditorInput().getAdapter(IResource.class);
			if (resource != null) {
				String extension = resource.getFileExtension();
				if (extension != null && extension.equals("pda")) {
					return new WkdLineBreakpointAdapter();
				}
			}			
		}
		return null;
	}
	
	@SuppressWarnings("rawtypes")
	public Class[] getAdapterList() {
		return new Class[]{IToggleBreakpointsTarget.class};
	}
}
