package com.tuxford.wkd.launch;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.ServerSocket;
import java.net.URL;
import java.util.TimeZone;

import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfig;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.ILaunchConfiguration;
import org.eclipse.debug.core.ILaunchManager;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.ILaunchConfigurationDelegate;
import org.eclipse.debug.core.model.IProcess;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.console.ConsolePlugin;
import org.eclipse.ui.console.IConsole;
import org.eclipse.ui.console.IConsoleConstants;
import org.eclipse.ui.console.IConsoleDocumentPartitioner;
import org.eclipse.ui.console.TextConsole;

import com.tuxford.wkd.debugclient.DebugClientBuilder;
import com.tuxford.wkd.debugclient.IDebugClient;
import com.tuxford.wkd.launch.cfg.KdConfiguration;
import com.tuxford.wkd.model.WkdDebugTarget;
import com.tuxford.wkd.model.WkdTarget;

public class WkdLaunchConfigurationDelegate implements  ILaunchConfigurationDelegate {

	@Override
	public void launch(ILaunchConfiguration launchConfiguration, String mode, ILaunch launch,
			IProgressMonitor progressMonitor) throws CoreException {
		
//	KdConfiguration kdConfiguration = KdConfiguration.buildUsingConfiguration(launchConfiguration);
	/* This code should be moved to separate class.
	 * At least elevation should be implemented as jni method or elevate.exe must be in the persistent directory.
	 * Problem with running process when path consists spaces should be solved. It seems it the problem of JDK.  
	 */
/*	final String connectionUrl = "http://localhost:21605/RPC2";
	XmlRpcClientConfigImpl clientConfig = new XmlRpcClientConfigImpl();
	try {
		clientConfig.setServerURL(new URL(connectionUrl));
		XmlRpcClient xmlrpcClient = new XmlRpcClient();
		xmlrpcClient.setConfig(clientConfig);
		Object params[] = {"test"};
		
		Boolean result = (Boolean)xmlrpcClient.execute("Kd.connect", params);
		System.out.println(result.toString());
		
	} catch (MalformedURLException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (XmlRpcException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}*/
//		IWorkbenchWindow workbenchWindow = PlatformUI.getWorkbench().getActiveWorkbenchWindow();
//		IWorkbenchPage activePage = workbenchWindow.getActivePage();
//		activePage.showView(IConsoleConstants.ID_CONSOLE_VIEW, null, IWorkbenchPage.VIEW_VISIBLE);
//		TextConsole textConsole = new TextConsole("Target", null, null, false) {
			
//			@Override
//			protected IConsoleDocumentPartitioner getPartitioner() {
//				// TODO Auto-generated method stub
//				return null;
//			}
//		};
//		ConsolePlugin.getDefault().getConsoleManager().addConsoles(new IConsole[]{textConsole});

//		IConsole[] consoles = ConsolePlugin.getDefault().getConsoleManager().getConsoles();
//		for(IConsole console : consoles) {
//			System.out.println("Console: " + console.getName() + " ;type=" + console.getType());
//		}
	

		if (!mode.equals(ILaunchManager.DEBUG_MODE)) {
			throw new CoreException(new Status(IStatus.CANCEL, DebugPlugin.getUniqueIdentifier(), "This plugin supports only debug mode."));
		}

		try {
			IDebugClient debugClient = DebugClientBuilder.build();
			IDebugTarget debugTarget = new WkdTarget(launch, debugClient);
			launch.addDebugTarget(debugTarget);
		} catch (Exception e) {
			throw new CoreException(new Status(IStatus.ERROR, DebugPlugin.getUniqueIdentifier(), e.getMessage()));
		}
		
	
/*		String commandLine = kdConfiguration.toString();
		String commandLineArray[] = new String[5];
		commandLineArray[0] = "e:\\elevation\\64\\elevate.exe";
		commandLineArray[1] = "-wait";
		commandLineArray[2] = commandLine;
		commandLineArray[3] = "-k";
		commandLineArray[4] = "1394:channel=1"; 
		try {
			Process process = DebugPlugin.exec(commandLineArray, null);
			IProcess wrappedProcess = DebugPlugin.newProcess(launch, process, commandLine);
			if (mode.equals(ILaunchManager.DEBUG_MODE)) {
				IDebugTarget target = new WkdDebugTarget(launch, wrappedProcess, process.getInputStream(), process.getOutputStream(), process.getErrorStream());
				launch.addDebugTarget(target);
				
			}
			
		} catch (Exception e1) {
			System.out.println(e1.getMessage());
		}
		
		try {
			Process kdProcess = DebugPlugin.exec(commandLineArray, null);
			kdProcess.getInputStream();
		} 
		catch(CoreException e) {
			System.out.println(e.getMessage());
		}
		catch(Exception e) {
			System.out.println(e.getMessage());
		}
		
//		int eventPort = findFreePort();*/		
		
		System.out.println("test");
	}
	
	public static int findFreePort() {
		ServerSocket socket= null;
		try {
			socket= new ServerSocket(0);
			return socket.getLocalPort();
		} catch (IOException e) { 
		} finally {
			if (socket != null) {
				try {
					socket.close();
				} catch (IOException e) {
				}
			}
		}
		return -1;		
	}		

}
