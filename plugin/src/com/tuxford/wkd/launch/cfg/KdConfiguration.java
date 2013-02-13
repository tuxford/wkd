package com.tuxford.wkd.launch.cfg;

import org.eclipse.core.runtime.CoreException;
import org.eclipse.debug.core.ILaunchConfiguration;


public class KdConfiguration {

	public class IeeeConfiguration {
		public static final String IEEE_CHANNEL = "ieeeChannel";

		private int ieeeChannel;

		public IeeeConfiguration(int ieeeChannel) {
			this.ieeeChannel = ieeeChannel;
		}
		
		public int getIeeeChannel() {
			return ieeeChannel;
		}

		public void setIeeeChannel(int ieeeChannel) {
			this.ieeeChannel = ieeeChannel;
		}
		
		public String toString() {
			return "-k 1394:channel=" + String.valueOf(getIeeeChannel());
		}
	}
	
	public static final String KD_EXECUTABLE = "kdExecutable";
	public static final String KD_CONNECTION_TYPE = "connectionType";
	
	private String kdExePath = null;
	private KdConnectionType kdConnectionType = null;
	private Object connectionConfiguration = null;
	
	private KdConfiguration() {
	}
	
	public String toString() {
		return "\"" + kdExePath + "\" ";// + connectionConfiguration.toString();
	}
	
	public static KdConfiguration buildUsingConfiguration(ILaunchConfiguration launchConfiguration) {
		KdConfiguration kdConfiguration = new KdConfiguration();
				
		try {
			kdConfiguration.kdExePath = getValueFromConfiguration(launchConfiguration, KD_EXECUTABLE);
			kdConfiguration.kdConnectionType = KdConnectionType.forValue(Integer.valueOf(getValueFromConfiguration(launchConfiguration, KD_CONNECTION_TYPE)));
			switch (kdConfiguration.kdConnectionType) {
			case IEEE:
				kdConfiguration.initIeeeConfiguation(Integer.valueOf(getValueFromConfiguration(launchConfiguration, IeeeConfiguration.IEEE_CHANNEL)));
				break;

			default:
				throw new RuntimeException("Currently only ieee1394 connection is supported");
			}
		} catch (CoreException e) {
			throw new RuntimeException("Runtime during load kd configuration");
		}
		
		return kdConfiguration;
		
	}
	
	private static String getValueFromConfiguration(ILaunchConfiguration launchConfiguration, String variableKey) throws CoreException {
		String kdExePathVariable = launchConfiguration.getAttribute(variableKey, (String)null);
		if ((kdExePathVariable == null) || kdExePathVariable.isEmpty()) {
			throw new RuntimeException("No variable " + variableKey + " found");
		}
		
		return kdExePathVariable;
		
	}
	
	private void initIeeeConfiguation(int ieeePort) {
		connectionConfiguration = new IeeeConfiguration(ieeePort);
	}
}
