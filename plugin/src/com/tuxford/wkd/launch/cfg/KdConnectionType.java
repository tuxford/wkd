package com.tuxford.wkd.launch.cfg;

import java.util.HashMap;
import java.util.Map;

public enum KdConnectionType {
	IEEE(0),
	SERIAL(1),
			
	UNKNOWN(-1);
	
	private static final Map<Integer, KdConnectionType> typesByValue = new HashMap<Integer, KdConnectionType>();
	final int value;
	
	static {
		for (KdConnectionType type : KdConnectionType.values()) {
			typesByValue.put(type.value, type);
		}
	}
	
	private KdConnectionType(int value) {
		this.value = value;
	}
	
	public static KdConnectionType forValue(int value) {
		return typesByValue.get(value);
	}

	public int getValue() {
		return value;
	}
	
	public static KdConnectionType valueOf(int intValue) {
		return typesByValue.get(intValue);
	}
}