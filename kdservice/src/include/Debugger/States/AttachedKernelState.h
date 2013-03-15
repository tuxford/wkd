/*
 * AttachedKernelState.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_States_AttachedKernelState_H_
#define Debugger_States_AttachedKernelState_H_

#include "Debugger/StateMachine.h"
#include "Debugger/Events/DisconnectEvent.h"
#include "Debugger/Events/RanEvent.h"

#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace Debugger {
namespace States {

class AttachedKernelState: public boost::statechart::state<AttachedKernelState, StateMachine> {
public:
	typedef boost::mpl::list<
			boost::statechart::custom_reaction<Events::DisconnectEvent>,
			boost::statechart::custom_reaction<Events::RanEvent>
			> reactions;

	static const StateId THIS_STATE_ID;

	AttachedKernelState(my_context cxt);

	virtual ~AttachedKernelState();

	boost::statechart::result react(const Events::DisconnectEvent& disconnectEvent);
	boost::statechart::result react(const Events::RanEvent& ranEvent);

private:

	void updateContext();
};

} /* namespace States */
} /* namespace Debugger */

#endif /* Debugger_States_AttachedKernelState_H_ */
