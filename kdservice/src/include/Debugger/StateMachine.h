/*
 * StateMachine.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_StateMachine_H_
#define Debugger_StateMachine_H_

#include "Debugger/States/TargetStateInfo.h"
#include "Debugger/IClient.h"
#include "Notifier/DebugEventRpcSender.h"

#include <boost/statechart/state_machine.hpp>
#include <boost/shared_ptr.hpp>

namespace Debugger {

namespace States {
class InitialState;
}  // namespace States

class StateMachine : public boost::statechart::state_machine<StateMachine, States::InitialState> {
public:
	StateMachine(boost::shared_ptr<Debugger::IClient> pClient);

	States::TargetStateInfo getTargetStateInfo() const;
	void updateTargetStateInfo(const States::TargetStateInfo& targetStateInfo);
	boost::shared_ptr<Debugger::IClient> getDebugClient() const;

private:
	States::TargetStateInfo targetStateInfo;
	boost::shared_ptr<Debugger::IClient> pDebugClient;
	Notifier::DebugEventRpcSender debugEventSender;

};

} /* namespace Debugger */
#endif /* Debugger_StateMachine_H_ */
