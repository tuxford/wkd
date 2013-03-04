/*
 * ConnectedState.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/States/ConnectedState.h"
#include "Debugger/States/AttachedKernelState.h"
#include "Debugger/Debugger.h"
#include "Service.h"

namespace Debugger {
namespace States {

const StateId ConnectedState::THIS_STATE_ID = "connected";

ConnectedState::ConnectedState(ConnectedState::my_context cxt) :
		my_base( cxt ){
	Service::LOGGER << log4cpp::Priority::DEBUG << "ConnectedState::ConnectedState";
}

ConnectedState::~ConnectedState() {
}

boost::statechart::result ConnectedState::react(const Events::AttachKernelEvent& attachKernelEvent) {
	try {
		Service::LOGGER << log4cpp::Priority::DEBUG << "ConnectedState::react: 0";
		context<StateMachine>().getDebugClient()->attachKenel(attachKernelEvent.getAttachKernelParams());
		Service::LOGGER << log4cpp::Priority::DEBUG << "ConnectedState::react: 1";
		context<StateMachine>().updateTargetStateInfo(ConnectedState::getStateContext());
		Service::LOGGER << log4cpp::Priority::DEBUG << "ConnectedState::react: 2";
	}
	catch(DebugClientException &e) {
		if (e.getErrorCode() != ALREADY_ATTACHED_KERNEL) {
//TODO: implement generic error handling
			return discard_event();
		}
	}

	return transit<AttachedKernelState>();
}

TargetStateInfo ConnectedState::getStateContext() {

	TargetStateInfo targetStateInfo;
	targetStateInfo.canDisconnect = true;
	targetStateInfo.canResume = false;
	targetStateInfo.canSuspend = false;
	targetStateInfo.canTerminate = false;
	targetStateInfo.isDisconnected = false;
	targetStateInfo.isSuspended = false;
	targetStateInfo.isTerminated = false;
	targetStateInfo.stateId = THIS_STATE_ID;

	return targetStateInfo;
}


} /* namespace States */
} /* namespace Debugger */
