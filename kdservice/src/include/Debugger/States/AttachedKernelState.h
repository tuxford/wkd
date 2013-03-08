/*
 * AttachedKernelState.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_States_AttachedKernelState_H_
#define Debugger_States_AttachedKernelState_H_

#include "Debugger/StateMachine.h"

#include <boost/statechart/state.hpp>

namespace Debugger {
namespace States {

class AttachedKernelState: public boost::statechart::state<AttachedKernelState, StateMachine> {
public:
	AttachedKernelState(my_context cxt);

	virtual ~AttachedKernelState();

private:
	static const StateId THIS_STATE_ID;

	void updateContext();
};

} /* namespace States */
} /* namespace Debugger */

#endif /* Debugger_States_AttachedKernelState_H_ */
