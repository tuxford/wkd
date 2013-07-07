/*
 * AttachedKernelState.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/States/AttachedKernelState.h"
#include "Debugger/States/InitialState.h"
#include "Debugger/States/RunState.h"
#include "Debugger/Debugger.h"
#include "Service.h"

namespace Debugger {
namespace States {

const StateId AttachedKernelState::THIS_STATE_ID = "attachedKernel";

AttachedKernelState::AttachedKernelState(my_context cxt) :
	my_base(cxt) {
	BOOST_LOG_TRIVIAL(debug) << "AttachedKernelState::AttachedKernelState";
	updateContext();
}

AttachedKernelState::~AttachedKernelState() {
}

boost::statechart::result AttachedKernelState::react(const Events::DisconnectEvent& disconnectEvent) {
	try {
		context<StateMachine>().getDebugClient()->disconnect();
		BOOST_LOG_TRIVIAL(debug) << "AttachedKernelState::react(Events::DisconnectEvent): disconnect from target";
	}
	catch(DebugClientException &e) {
//TODO: implement generic error handling
		BOOST_LOG_TRIVIAL(debug) << "AttachedKernelState::react(Events::DisconnectEvent): disconnect failed with exception: " << e.getMessage();
		return discard_event();
	}
	catch(...) {
//TODO: implement generic error handling
		BOOST_LOG_TRIVIAL(debug) << "AttachedKernelState::react(Events::DisconnectEvent): disconnect failed with unknown exception" ;
		return discard_event();
	}

	return transit<InitialState>();
}

boost::statechart::result AttachedKernelState::react(const Events::RanEvent& goEvent) {
	return transit<RunState>();
}

void AttachedKernelState::updateContext() {

	TargetStateInfo targetStateInfo;
	targetStateInfo.canDisconnect = true;
	targetStateInfo.canResume = false;
	targetStateInfo.canSuspend = true;
	targetStateInfo.canTerminate = false;
	targetStateInfo.isDisconnected = false;
	targetStateInfo.isSuspended = false;
	targetStateInfo.isTerminated = false;
	targetStateInfo.stateId = THIS_STATE_ID;

	context<StateMachine>().updateTargetStateInfo(targetStateInfo);
}

} /* namespace States */
} /* namespace Debugger */
