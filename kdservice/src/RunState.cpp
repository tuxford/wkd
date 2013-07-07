/*
 * RunState.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/States/RunState.h"
#include "Debugger/Debugger.h"

#include "Service.h"

namespace Debugger {
namespace States {

const StateId RunState::STATE_ID = "run";

RunState::RunState(RunState::my_context cxt) : my_base(cxt)
{
	BOOST_LOG_TRIVIAL(debug) << "RunState::RunState";
	updateContext();
}

RunState::~RunState() {

}
/*
boost::statechart::result RunState::react(const Events::GoEvent& event) {
	BOOST_LOG_TRIVIAL(debug) << "RunState::react: debugger transit in the initial state from " << context<StateMachine>().getTargetStateInfo().stateId;

	updateContext();

	return discard_event();
}*/


void RunState::updateContext() {
	TargetStateInfo targetStateInfo;
	targetStateInfo.canDisconnect = false;
	targetStateInfo.canResume = false;
	targetStateInfo.canSuspend = true;
	targetStateInfo.canTerminate = false;
	targetStateInfo.isDisconnected = true;
	targetStateInfo.isSuspended = false;
	targetStateInfo.isTerminated = false;
	targetStateInfo.stateId = STATE_ID;

	context<StateMachine>().updateTargetStateInfo(targetStateInfo);
}

} /* namespace States */
} /* namespace Debugger */
