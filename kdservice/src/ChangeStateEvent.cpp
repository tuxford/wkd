/*
 * ChangeStateEvent.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: Roman Luchyshyn
 */

#include "Notifier/Events/ChangeStateEvent.h"

namespace Notifier {
namespace Events {

ChangeStateEvent::ChangeStateEvent(const Debugger::States::TargetStateInfo& targetState) :
	targetStateInfo(targetState) {
}

Debugger::States::TargetStateInfo ChangeStateEvent::getTargetStateInfo() const {
	return targetStateInfo;
}

}  // namespace Events
} /* namespace Notifier */
