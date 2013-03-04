/*
 * StateMachine.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/StateMachine.h"
#include "Debugger/States/InitialState.h"
#include "Notifier/Events/ChangeStateEvent.h"

#include "Service.h"

namespace Debugger {

StateMachine::StateMachine(boost::shared_ptr<Debugger::IClient> pClient) :
		pDebugClient(pClient) {
	Service::LOGGER << log4cpp::Priority::DEBUG << "StateMachine::StateMachine";
}

States::TargetStateInfo StateMachine::getTargetStateInfo() const {
	return targetStateInfo;
}

void StateMachine::updateTargetStateInfo(const States::TargetStateInfo& targetStateInfo) {
	try {
		this->targetStateInfo = targetStateInfo;
		debugEventSender.notify(Notifier::Events::ChangeStateEvent(targetStateInfo));
	}
	catch(...) {
		Service::LOGGER << log4cpp::Priority::DEBUG << "StateMachine::updateTargetStateInfo: can't send event.";
	}
}

boost::shared_ptr<Debugger::IClient> StateMachine::getDebugClient() const {
	return pDebugClient;
}

} /* namespace Debugger */
