/*
 * InitialState.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_States_InitialState_H_
#define Debugger_States_InitialState_H_

#include "Debugger/StateMachine.h"
#include "Debugger/Events/EntryEvent.h"
#include "Debugger/Events/ConnectEvent.h"

#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace Debugger {
namespace States {

class InitialState: public boost::statechart::state<InitialState, StateMachine> {
public:
	typedef boost::mpl::list<
			boost::statechart::custom_reaction<Events::EntryEvent>,
			boost::statechart::custom_reaction<Events::ConnectEvent>
			> reactions;

	InitialState(my_context context);
	virtual ~InitialState();

	boost::statechart::result react(const Events::EntryEvent& event);
	boost::statechart::result react(const Events::ConnectEvent& event);

private:
	void updateContext();

	static const StateId THIS_STATE_ID;
};

} /* namespace States */
} /* namespace Debugger */

#endif /* Debugger_States_InitialState_H_ */
