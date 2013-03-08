/*
 * ConnectedState.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_States_ConnectedState_H_
#define Debugger_States_ConnectedState_H_

#include "Debugger/StateMachine.h"
#include "Debugger/Events/AttachKernelEvent.h"

#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace Debugger {
namespace States {

class ConnectedState: public boost::statechart::state<ConnectedState, StateMachine> {
public:
	typedef boost::mpl::list<boost::statechart::custom_reaction<Events::AttachKernelEvent> > reactions;

	ConnectedState(my_context cxt);
	virtual ~ConnectedState();

	boost::statechart::result react(const Events::AttachKernelEvent& attachKernelEvent);

private:
	static const StateId THIS_STATE_ID;

	void updateContext();
};

} /* namespace States */
} /* namespace Debugger */

#endif /* Debugger_States_ConnectedState_H_ */
