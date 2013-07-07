/*
 * ConnectedState.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/States/ConnectedState.h"
#include "Debugger/States/AttachedKernelState.h"
#include "Debugger/States/InitialState.h"

#include "Debugger/Debugger.h"
#include "Service.h"

namespace Debugger {
namespace States {

const StateId ConnectedState::THIS_STATE_ID = "connected";

ConnectedState::ConnectedState(my_context cxt) :
		my_base(cxt){
	BOOST_LOG_TRIVIAL(debug) << "ConnectedState::ConnectedState";
	updateContext();
}

ConnectedState::~ConnectedState() {
}

boost::statechart::result ConnectedState::react(const Events::AttachKernelEvent& attachKernelEvent) {
	BOOST_LOG_TRIVIAL(debug) << "ConnectedState::react: entry";
	try {
		context<StateMachine>().getDebugClient()->attachKenel(attachKernelEvent.getAttachKernelParams());
	}
	catch(DebugClientException &e) {
		if (e.getErrorCode() != ALREADY_ATTACHED_KERNEL) {
//TODO: implement generic error handling
			return discard_event();
		}
	}
	catch(...) {
		//TODO: implement generic error handling
		return discard_event();
	}

	return transit<AttachedKernelState>();
}

boost::statechart::result ConnectedState::react(const Events::DisconnectEvent& disconnectEvent) {
	try {
		context<StateMachine>().getDebugClient()->disconnect();
		BOOST_LOG_TRIVIAL(debug) << "ConnectedState::react(Events::DisconnectEvent): disconnect from target";
	}
	catch(DebugClientException &e) {
//TODO: implement generic error handling
		BOOST_LOG_TRIVIAL(debug) << "ConnectedState::react(Events::DisconnectEvent): disconnect failed with exception: " << e.getMessage();
		return discard_event();
	}
	catch(...) {
//TODO: implement generic error handling
		BOOST_LOG_TRIVIAL(debug) << "ConnectedState::react(Events::DisconnectEvent): disconnect failed with unknown exception" ;
		return discard_event();
	}

	return transit<InitialState>();
}

void ConnectedState::updateContext() {

	TargetStateInfo targetStateInfo;
	targetStateInfo.canDisconnect = true;
	targetStateInfo.canResume = false;
	targetStateInfo.canSuspend = false;
	targetStateInfo.canTerminate = false;
	targetStateInfo.isDisconnected = false;
	targetStateInfo.isSuspended = false;
	targetStateInfo.isTerminated = false;
	targetStateInfo.stateId = THIS_STATE_ID;

	context<StateMachine>().updateTargetStateInfo(targetStateInfo);
}


} /* namespace States */
} /* namespace Debugger */
