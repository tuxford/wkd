/*
 * AttachedKernelState.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/States/AttachedKernelState.h"
#include "Service.h"

namespace Debugger {
namespace States {

const StateId AttachedKernelState::THIS_STATE_ID = "attachedKernel";

AttachedKernelState::AttachedKernelState(my_context cxt) :
	my_base(cxt) {
	Service::LOGGER << log4cpp::Priority::DEBUG << "AttachedKernelState::AttachedKernelState";
	updateContext();
}

AttachedKernelState::~AttachedKernelState() {
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
