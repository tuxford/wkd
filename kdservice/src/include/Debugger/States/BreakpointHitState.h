/*
 * BreakpointHitState.h
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_States_BreakpointHitState_H_
#define Debugger_States_BreakpointHitState_H_

#include "Debugger/StateMachine.h"

#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace Debugger {
namespace States {

class BreakpointHitState: public boost::statechart::state<BreakpointHitState, StateMachine> {
public:
/*	typedef boost::mpl::list<
			boost::statechart::custom_reaction<Events::GoEvent>
			> reactions;*/

	static const StateId STATE_ID;

	BreakpointHitState(my_context context);
	virtual ~BreakpointHitState();

//	boost::statechart::result react(const Events::GoEvent& event);

private:
	void updateContext();
};

} /* namespace States */
} /* namespace Debugger */

#endif /* Debugger_States_BreakpointHitState_H_ */
