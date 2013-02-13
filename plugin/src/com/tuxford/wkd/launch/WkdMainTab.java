package com.tuxford.wkd.launch;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.Status;
import org.eclipse.debug.core.ILaunchConfiguration;
import org.eclipse.debug.core.ILaunchConfigurationWorkingCopy;
import org.eclipse.debug.ui.AbstractLaunchConfigurationTab;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.SashForm;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.widgets.TabItem;
import org.eclipse.swt.widgets.Text;

import com.tuxford.wkd.launch.cfg.IWkdConstants;
import com.tuxford.wkd.launch.cfg.KdConfiguration;
import com.tuxford.wkd.launch.cfg.KdConnectionType;

public class WkdMainTab extends AbstractLaunchConfigurationTab {
	
	private Text kdText;
	private Button kdSelectButton;
	private TabFolder kdConnectionTypeTab;
	private Text channelText;
	
	public void createControl(Composite parent) {
		Font font = parent.getFont();
		
		Composite comp = new Composite(parent, SWT.NONE);
		setControl(comp);
		GridLayout topLayout = new GridLayout();
		topLayout.verticalSpacing = 0;
		topLayout.numColumns = 3;
		comp.setLayout(topLayout);
		comp.setFont(font);
		
		createVerticalSpacer(comp, 3);
		
		Label programLabel = new Label(comp, SWT.NONE);
		programLabel.setText("kd.exe &execubable location:");
		GridData gd = new GridData(GridData.BEGINNING);
		programLabel.setLayoutData(gd);
		programLabel.setFont(font);
		
		kdText = new Text(comp, SWT.SINGLE | SWT.BORDER);
		gd = new GridData(GridData.FILL_HORIZONTAL);
		kdText.setLayoutData(gd);
		kdText.setFont(font);
		kdText.addModifyListener(new ModifyListener() {
			public void modifyText(ModifyEvent e) {
				updateLaunchConfigurationDialog();
			}
		});
		
		kdSelectButton = createPushButton(comp, "&Browse...", null); //$NON-NLS-1$
		kdSelectButton.addSelectionListener(new SelectionAdapter() {
			public void widgetSelected(SelectionEvent e) {
				browseKdExeFile();
			}
		});
		
		createVerticalSpacer(comp, 1);
		
		Label kdSetupLabel = new Label(comp, SWT.NONE);
		kdSetupLabel.setText("KD settings:");
		GridData kdSetupGd = new GridData(GridData.BEGINNING );
		kdSetupGd.horizontalSpan = 3;
		kdSetupLabel.setLayoutData(kdSetupGd);
		kdSetupLabel.setFont(font);
		
		kdConnectionTypeTab = new TabFolder(comp, SWT.NONE);
		kdConnectionTypeTab.setBackground(parent.getBackground());
		GridData kdConnectionTabSetupGd = new GridData(GridData.BEGINNING);
		kdConnectionTabSetupGd.horizontalSpan = 3;
		kdConnectionTypeTab.setLayout(new FillLayout());
		kdConnectionTypeTab.setLayoutData(kdConnectionTabSetupGd);
		
		TabItem ieeeTabItem = new TabItem(kdConnectionTypeTab, SWT.NONE);
		ieeeTabItem.setText("IEEE 1394");
		
		SashForm ieeeSetupSf = new SashForm(kdConnectionTypeTab, SWT.HORIZONTAL);
		Label channelLabel = new Label(ieeeSetupSf, SWT.NONE);
		channelLabel.setText("Channel: ");
		
		channelText = new Text(ieeeSetupSf, SWT.SINGLE | SWT.BORDER);
//		channelText.setText("1");
		channelText.addModifyListener(new ModifyListener() {
			public void modifyText(ModifyEvent e) {
				updateLaunchConfigurationDialog();
			}
		});
		
		ieeeTabItem.setControl(ieeeSetupSf);
		
		TabItem serialTabItem = new TabItem(kdConnectionTypeTab, SWT.NONE);
		serialTabItem.setText("Serial");
		
		SashForm serialSf = new SashForm(kdConnectionTypeTab, SWT.HORIZONTAL);
		Label portLabel = new Label(serialSf, SWT.NONE);
		portLabel.setText("Port: ");
		serialTabItem.setControl(serialSf);
		
	}
	
	protected void browseKdExeFile() {
		FileDialog dialog = new FileDialog(getShell(), SWT.OPEN);
		
		String oldPath = kdText.getText();
		if ((oldPath !=null) && (oldPath.length() != 0))
		{
			dialog.setFileName(oldPath);
		}
		
		dialog.setText("kd.exe Program");
		String kdExeFile=dialog.open();
		if (kdExeFile != null) {
			kdText.setText(kdExeFile);
		}
	}

	public void setDefaults(ILaunchConfigurationWorkingCopy configuration) {
	}

	public void initializeFrom(ILaunchConfiguration configuration) {
		try {
			String program = configuration.getAttribute(IWkdConstants.ATTR_PDA_PROGRAM, (String)null);
			if (program != null) {
				kdText.setText(program);
			}
			
			String kdConnnectionTypeStr = configuration.getAttribute(KdConfiguration.KD_CONNECTION_TYPE, (String)null);
			if (kdConnnectionTypeStr == null) {
				kdConnnectionTypeStr = "0";
			}
			
			KdConnectionType kdConnectionType = KdConnectionType.valueOf(Integer.valueOf(kdConnnectionTypeStr).intValue());
			if (kdConnectionType != KdConnectionType.UNKNOWN) {
				kdConnectionTypeTab.setSelection(kdConnectionType.getValue());
			}
			else {
				throw new CoreException(new Status(Status.ERROR, "com.rainbow.wkd", "Unknow connection type"));
			}
			
			switch (kdConnectionType) {
			case IEEE:
				String ieeeChannelStr = configuration.getAttribute(KdConfiguration.IeeeConfiguration.IEEE_CHANNEL, (String)null);
				if (ieeeChannelStr == null) {
					ieeeChannelStr = "1";
				}
				Integer.valueOf(ieeeChannelStr);
				channelText.setText(ieeeChannelStr);
				break;
				default:
			}
			
		} catch (CoreException e) {
			if (e != null) {
				setErrorMessage(e.getMessage());
			} 
		}
	}

	public void performApply(ILaunchConfigurationWorkingCopy configuration) {
		performUpdateKdExe(configuration);
		performUpdateKdSettings(configuration);
	}

	public String getName() {
		return "Main";
	}

	public boolean isValid(ILaunchConfiguration launchConfig) {
		String text = kdText.getText();
		if (text.length() > 0) {
			IPath path = new Path(text);
			int lastSegment = path.segmentCount() - 1;
			if (!path.segment(lastSegment).equals("kd.exe") ) {
				setMessage("kd.exe not found");
				return false;
			}
			
			try {
				Process kdGetVersion = Runtime.getRuntime().exec("\"" + text + "\" -version");
				int exitValue = kdGetVersion.waitFor();
				if (exitValue != 0) {
					setMessage("kd returned " + String.valueOf(exitValue));
					return false;
				}
				InputStream is = kdGetVersion.getInputStream();
				InputStreamReader isr = new InputStreamReader(is);
				BufferedReader reader = new BufferedReader(isr);
				String outputStr = reader.readLine().trim().toLowerCase();
				
				String beginOfOutput = "kd version ";
				if (outputStr.startsWith(beginOfOutput)) {
					String version = outputStr.substring(beginOfOutput.length(), outputStr.length()-1);
					StringTokenizer tokenizer = new StringTokenizer(version, ".");
					String majorVerionStr = tokenizer.nextToken();
					int majorVersion = Integer.valueOf(majorVerionStr).intValue();
					if (majorVersion != 6) {
						setMessage("This plugin support on kd of version 6");
					}
				}
				else {
					setMessage("Can't determine debugger's version");
				}
			} catch (IOException | InterruptedException e) {
				setMessage("Can't run a kd.exe");
			}
		} else {
			setMessage("Specify a program");
		}
		
		KdConnectionType kdConnectionType =  KdConnectionType.forValue(kdConnectionTypeTab.getSelectionIndex());
		if (kdConnectionType.equals(KdConnectionType.IEEE)) {
			int ieeeChannl = Integer.parseInt(channelText.getText());
			if (ieeeChannl < 0) {
				setMessage("Invalid channel id");
				return false;
			}
		}
		else {
			setMessage("Currently we support only ieee1394 interface");
			return false;
		}
		
		return super.isValid(launchConfig);
	}
	
	private void performUpdateKdExe(ILaunchConfigurationWorkingCopy configuration) {
		String program = kdText.getText().trim();
		if (program.length() == 0) {
			program = null;
		}
		configuration.setAttribute(KdConfiguration.KD_EXECUTABLE, program);		
	}
	
	private void performUpdateKdSettings(ILaunchConfigurationWorkingCopy configuration) {
		
		int selectionId = kdConnectionTypeTab.getSelectionIndex();
		
		if (selectionId == 0) {			
			int ieeeChannel = 0;
			String channelTextValue = channelText.getText().trim();
			try {
				ieeeChannel = Integer.valueOf(channelTextValue).intValue();
				if (ieeeChannel < 0) {
					ieeeChannel = 1;
				}
			}
			catch(NumberFormatException e) {
				ieeeChannel = 1;
			}
			
			configuration.setAttribute(KdConfiguration.IeeeConfiguration.IEEE_CHANNEL, String.valueOf(ieeeChannel));
			configuration.setAttribute(KdConfiguration.KD_CONNECTION_TYPE, "0");
		}
	}
}
