package com.tuxford.wkd.ui.pda.launching;

import org.eclipse.debug.ui.AbstractLaunchConfigurationTabGroup;
import org.eclipse.debug.ui.CommonTab;
import org.eclipse.debug.ui.ILaunchConfigurationDialog;
import org.eclipse.debug.ui.ILaunchConfigurationTab;
import org.eclipse.debug.ui.sourcelookup.SourceLookupTab;

import com.tuxford.wkd.launch.WkdMainTab;

public class WkdTabGroup extends AbstractLaunchConfigurationTabGroup {
	public void createTabs(ILaunchConfigurationDialog dialog, String mode) {
		setTabs(new ILaunchConfigurationTab[] {
				new WkdMainTab(),
				new SourceLookupTab(),
				new CommonTab()
		});
	}
}
