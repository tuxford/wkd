/*
 * AttachedKernelState.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_States_AttachedKernelState_H_
#define Debugger_States_AttachedKernelState_H_

#include "Debugger/StateMachine.h"

#include <boost/statechart/simple_state.hpp>

namespace Debugger {
namespace States {

class AttachedKernelState: public boost::statechart::simple_state<AttachedKernelState, StateMachine> {
public:
	AttachedKernelState();

	virtual ~AttachedKernelState();

private:
	static const StateId THIS_STATE_ID;
};

} /* namespace States */
} /* namespace Debugger */

#endif /* Debugger_States_AttachedKernelState_H_ */
