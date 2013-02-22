/*
 * EventSerializer.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: Roman Luchyshyn
 */

#include "Notifier/EventSerializer.h"

namespace Notifier {

/**
 * Format is next.
 * First line is structure name only.
 * Next lines are values in format name=type:value
 */
std::string EventSerializer::servialize(const Events::ChangeStateEvent& event) {
/*
 	StateId stateId;
	bool canTerminate;
	bool isTerminated;
	bool canResume;
	bool canSuspend;
	bool isSuspended;
	bool canDisconnect;
	bool isDisconnected;

 */
	std::string result;
	result += "ChangeStateEvent\n";
	result += "stateId=string:" + event.getTargetStateInfo().stateId + "\n";
	result += boolToString("canTerminate", event.getTargetStateInfo().canTerminate);
	result += boolToString("isTerminated", event.getTargetStateInfo().isTerminated);
	result += boolToString("canResume", event.getTargetStateInfo().canResume);
	result += boolToString("canSuspend", event.getTargetStateInfo().canSuspend);
	result += boolToString("isSuspended", event.getTargetStateInfo().isSuspended);
	result += boolToString("canDisconnect", event.getTargetStateInfo().canDisconnect);
	result += boolToString("isDisconnected", event.getTargetStateInfo().isDisconnected);

	return result;
}

std::string EventSerializer::boolToString(const std::string& valueId, bool value) {
	std::string result = valueId + "=" + "bool:" + (value ? "1" : "0") + "\n";

	return result;
}

} /* namespace Debugger */
