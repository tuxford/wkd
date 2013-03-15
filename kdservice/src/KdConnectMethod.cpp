/*
 * KdConnectMethod.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/Impl/KdConnectMethod.h"
#include "Server/Methods/Methods.h"
#include "Debugger/Debugger.h"
#include "Debugger/Events/ConnectEvent.h"
#include "Debugger/States/InitialState.h"
#include "Service.h"

#include <iostream>
#include <exception>

namespace Server {
namespace Methods {

const std::string KdConnectMethod::RPC_METHOD_NAME = "Kd.connect";
const std::string KdConnectMethod::RPC_SIGNATURE = "i:";

KdConnectMethod::KdConnectMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine_) :
		AbstractAsynchronousMethod(RPC_METHOD_NAME, RPC_SIGNATURE),
			pStateMachine(pStateMachine_) {
}

unsigned int KdConnectMethod::isActionCanceled() const {
	if (pStateMachine->getTargetStateInfo().stateId == Debugger::States::InitialState::STATE_ID) {
		return NO_CANCEL;
	}
	else {
		return INVALID_STATE;
	}
}

void KdConnectMethod::handleParameters(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
}

void KdConnectMethod::doAction() {
	pStateMachine->process_event(Debugger::Events::ConnectEvent());
}

} /* namespace Methods */
} /* namespace Server */
