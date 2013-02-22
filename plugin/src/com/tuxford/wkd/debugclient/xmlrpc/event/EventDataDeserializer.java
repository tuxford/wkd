package com.tuxford.wkd.debugclient.xmlrpc.event;

import com.tuxford.wkd.debugclient.ITargetState;
import com.tuxford.wkd.debugclient.xmlrpc.RpcTargetState;

public class EventDataDeserializer {

	private static final Object TARGET_STATE_HEADER_ID = "ChangeStateEvent";
	private static int STRUCT_LINES_COUNT = 9;

	public static ITargetState deserializeTargetState(String serialized) {
		RpcTargetState targetState = new RpcTargetState();
		
		String[] dataByLine = serialized.trim().split("\n");
		
		checkTargetStateIntegrity(dataByLine);

		for (int i=1; i<dataByLine.length; ++i) {
			String valueReString[] = parseValueRecord(dataByLine[i]);
			switch (valueReString[0]) {
			case "stateId":	
				targetState.setStateId(deserializeStringValue(valueReString[1]));
				break;
			case "canDisconnect":
				targetState.setCanDisconnect(deserilizeBoolValue(valueReString[1]));
				break;
			case "canResume":
				targetState.setCanResume(deserilizeBoolValue(valueReString[1]));
				break;
			case "canSuspend":
				targetState.setCanSuspend(deserilizeBoolValue(valueReString[1]));
				break;
			case "canTerminate":
				targetState.setCanTerminate(deserilizeBoolValue(valueReString[1]));
				break;
			case "isDisconnected":
				targetState.setDisconnected(deserilizeBoolValue(valueReString[1]));
				break;
			case "isSuspended":
				targetState.setSuspended(deserilizeBoolValue(valueReString[1]));
				break;
			case "isTerminated":
				targetState.setTerminated(deserilizeBoolValue(valueReString[1]));
				break;
			default:
				throw new IllegalArgumentException("Invalid field id");
			}
		}
		
		return targetState;
		
	}
	
	private static boolean deserilizeBoolValue(String valueRecord) {
		String[] parsedValue_Type = valueRecord.trim().split(":");
		
		if (parsedValue_Type.length != 2) {
			throw new IllegalArgumentException("Invalid value record format");
		}
		
		String type = parsedValue_Type[0];
		if (!type.equals("bool")) {
			throw new IllegalArgumentException("Invalid type");
		}
		
		int intValue = Integer.parseInt(parsedValue_Type[1]);
		boolean result = (intValue == 0) ? false : true; 
		return result;
	}

	private static String deserializeStringValue(String valueRecord) {
		String[] parsedValue_Type = valueRecord.trim().split(":");
		
		if (parsedValue_Type.length != 2) {
			throw new IllegalArgumentException("Invalid value record format");
		}
		
		String type = parsedValue_Type[0];
		if (!type.equals("string")) {
			throw new IllegalArgumentException("Invalid type");
		}
		
		String value = parsedValue_Type[1];
		return value;
	}

	private static void checkTargetStateIntegrity(String[] dataByLine) {
		if (dataByLine.length != STRUCT_LINES_COUNT) {
			throw new IllegalArgumentException("Invalid content size");
		}
		
		String header = dataByLine[0];
		if (!header.equals(TARGET_STATE_HEADER_ID)) {
			throw new IllegalArgumentException("Invalid header");
		}
	}
	
	private static String[] parseValueRecord(String valueRecord) {
	
		String[] parsedName_TypeValue = valueRecord.trim().split("=");
		if (parsedName_TypeValue.length != 2) {
			throw new IllegalArgumentException("Invalid value record format");
		}
		
		return parsedName_TypeValue;
	}


}
