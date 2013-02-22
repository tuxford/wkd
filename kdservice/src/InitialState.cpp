/*
 * InitialState.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/States/InitialState.h"
#include "Debugger/States/ConnectedState.h"
#include "Debugger/Debugger.h"

#include "Service.h"

namespace Debugger {
namespace States {

const StateId InitialState::THIS_STATE_ID = "initial";

InitialState::InitialState() {
	Service::LOGGER << log4cpp::Priority::DEBUG << "InitialState::InitialState";
}

InitialState::~InitialState() {

}

boost::statechart::result InitialState::react(const Events::EntryEvent& event) {
	Service::LOGGER << log4cpp::Priority::DEBUG << "InitialState::react: debugger transit in the initial state from " << context<StateMachine>().getTargetStateInfo().stateId;

	updateContext();

	return discard_event();
}

boost::statechart::result InitialState::react(const Events::ConnectEvent& event) {

	try {
		context<StateMachine>().getDebugClient()->connect();
		context<StateMachine>().updateTargetStateInfo(ConnectedState::getStateContext());
	}
	catch(DebugClientException &e) {
		if (e.getErrorCode() != ALREADY_INITILIZED) {
//TODO: implement generic error handling
			return discard_event();
		}
	}

	return transit<ConnectedState>();
}

void InitialState::updateContext() {
	TargetStateInfo targetStateInfo;
	targetStateInfo.canDisconnect = false;
	targetStateInfo.canResume = false;
	targetStateInfo.canSuspend = false;
	targetStateInfo.canTerminate = false;
	targetStateInfo.isDisconnected = true;
	targetStateInfo.isSuspended = false;
	targetStateInfo.isTerminated = true;
	targetStateInfo.stateId = "initial";

	context<StateMachine>().updateTargetStateInfo(targetStateInfo);
}

} /* namespace States */
} /* namespace Debugger */
