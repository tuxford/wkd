/*
 * ChangeStateEvent.h
 *
 *  Created on: Feb 19, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Notifier_Events_ChangeStateEvent_H_
#define Notifier_Events_ChangeStateEvent_H_

#include "Debugger/States/TargetStateInfo.h"

namespace Notifier {
namespace Events {

class ChangeStateEvent {
public:
	ChangeStateEvent(const Debugger::States::TargetStateInfo& targetState);

	Debugger::States::TargetStateInfo getTargetStateInfo() const;

private:
	Debugger::States::TargetStateInfo targetStateInfo;
};

}  // namespace Events
} /* namespace Notifier */

#endif /* Notifier_Events_ChangeStateEvent_H_ */
