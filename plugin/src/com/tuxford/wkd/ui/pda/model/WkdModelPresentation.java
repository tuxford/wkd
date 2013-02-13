package com.tuxford.wkd.ui.pda.model;

import org.eclipse.core.resources.IFile;
import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.model.ILineBreakpoint;
import org.eclipse.debug.core.model.IValue;
import org.eclipse.debug.ui.IDebugModelPresentation;
import org.eclipse.debug.ui.IValueDetailListener;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.part.FileEditorInput;

public class WkdModelPresentation extends LabelProvider implements IDebugModelPresentation {

	public void setAttribute(String attribute, Object value) {
	}

	public Image getImage(Object element) {
		return null;
	}

	public String getText(Object element) {
		return null;
	}

	public void computeDetail(IValue value, IValueDetailListener listener) {
		String detail = "";
		try {
			detail = value.getValueString();
		} catch (DebugException e) {
		}
		listener.detailComputed(value, detail);
	}

	public IEditorInput getEditorInput(Object element) {
		if (element instanceof IFile) {
			return new FileEditorInput((IFile)element);
		}
		if (element instanceof ILineBreakpoint) {
			return new FileEditorInput((IFile)((ILineBreakpoint)element).getMarker().getResource());
		}
		return null;
	}

	public String getEditorId(IEditorInput input, Object element) {
		if (element instanceof IFile || element instanceof ILineBreakpoint) {
			return "org.eclipse.ui.DefaultTextEditor";
		}
		return null;
	}
}
