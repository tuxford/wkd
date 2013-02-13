package com.tuxford.wkd.ui.pda.views;

import org.eclipse.core.runtime.IAdaptable;
import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.model.IDebugElement;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.ui.AbstractDebugView;
import org.eclipse.debug.ui.DebugUITools;
import org.eclipse.debug.ui.IDebugUIConstants;
import org.eclipse.jface.action.IMenuManager;
import org.eclipse.jface.action.IToolBarManager;
import org.eclipse.jface.action.Separator;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.ITreeContentProvider;
import org.eclipse.jface.viewers.TreeViewer;
import org.eclipse.jface.viewers.Viewer;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.ISelectionListener;
import org.eclipse.ui.IWorkbenchActionConstants;
import org.eclipse.ui.IWorkbenchPart;

import com.tuxford.wkd.launch.cfg.IWkdConstants;
import com.tuxford.wkd.model.WkdDebugTarget;

public class DataStackView extends AbstractDebugView implements ISelectionListener {
	
	class StackViewContentProvider implements ITreeContentProvider {

		public Object[] getChildren(Object parentElement) {
			if (parentElement instanceof WkdDebugTarget) {
				try {
					return ((WkdDebugTarget)parentElement).getDataStack();
				} catch (DebugException e) {
				}
			}
			return new Object[0];
		}

		public Object getParent(Object element) {
			if (element instanceof IDebugTarget) {
				return null;
			} else {
				return ((IDebugElement)element).getDebugTarget();
			}
		}

		public boolean hasChildren(Object element) {
			if (element instanceof IDebugElement) {
				return getChildren(element).length > 0;
			}
			return false;
		}

		public Object[] getElements(Object inputElement) {
			return getChildren(inputElement);
		}

		public void dispose() {
		}

		public void inputChanged(Viewer viewer, Object oldInput, Object newInput) {
		}		
	}
	
	protected Viewer createViewer(Composite parent) {
		TreeViewer viewer = new TreeViewer(parent);
		viewer.setLabelProvider(DebugUITools.newDebugModelPresentation());
		viewer.setContentProvider(new StackViewContentProvider());
		getSite().getWorkbenchWindow().getSelectionService().addSelectionListener(IDebugUIConstants.ID_DEBUG_VIEW, this);
		return viewer;
	}

	protected void createActions() {
	}

	protected String getHelpContextId() {
		return null;
	}

	protected void fillContextMenu(IMenuManager menu) {
		menu.add(new Separator(IWorkbenchActionConstants.MB_ADDITIONS));
	}

	protected void configureToolBar(IToolBarManager tbm) {
	}

	public void dispose() {
		getSite().getWorkbenchWindow().getSelectionService().removeSelectionListener(IDebugUIConstants.ID_DEBUG_VIEW, this);
		super.dispose();
	}

	public void selectionChanged(IWorkbenchPart part, ISelection selection) {
		IAdaptable adaptable = DebugUITools.getDebugContext();
		Object input = null;
		if (adaptable != null) {
			IDebugElement element = (IDebugElement) adaptable.getAdapter(IDebugElement.class);
			if (element != null) {
				if (element.getModelIdentifier().equals(IWkdConstants.ID_PDA_DEBUG_MODEL)) {
					input = element.getDebugTarget();
				}
			}
		} 
		getViewer().setInput(input);
	}
}
