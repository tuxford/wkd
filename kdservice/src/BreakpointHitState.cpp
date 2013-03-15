/*
 * BreakpointHitState.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/States/BreakpointHitState.h"
#include "Debugger/Debugger.h"

#include "Service.h"

namespace Debugger {
namespace States {

const StateId BreakpointHitState::STATE_ID = "breakpointHit";

BreakpointHitState::BreakpointHitState(BreakpointHitState::my_context cxt) : my_base(cxt)
{
	Service::LOGGER << log4cpp::Priority::DEBUG << "BreakpointHitState::BreakpointHitState";
	updateContext();
}

BreakpointHitState::~BreakpointHitState() {

}
/*
boost::statechart::result BreakpointHitState::react(const Events::GoEvent& event) {
	Service::LOGGER << log4cpp::Priority::DEBUG << "BreakpointHitState::react: debugger transit in the initial state from " << context<StateMachine>().getTargetStateInfo().stateId;

	updateContext();

	return discard_event();
}*/


void BreakpointHitState::updateContext() {
	TargetStateInfo targetStateInfo;
	targetStateInfo.canDisconnect = false;
	targetStateInfo.canResume = true;
	targetStateInfo.canSuspend = false;
	targetStateInfo.canTerminate = false;
	targetStateInfo.isDisconnected = true;
	targetStateInfo.isSuspended = true;
	targetStateInfo.isTerminated = false;
	targetStateInfo.stateId = STATE_ID;

	context<StateMachine>().updateTargetStateInfo(targetStateInfo);
}

} /* namespace States */
} /* namespace Debugger */
