/*
 * KdDisconnectMethod.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/Impl/KdDisconnectMethod.h"
#include "Server/Methods/Methods.h"
#include "Debugger/Debugger.h"
#include "Debugger/Events/ConnectEvent.h"
#include "Debugger/States/AttachedKernelState.h"
#include "Service.h"

#include <iostream>
#include <exception>

namespace Server {
namespace Methods {

const std::string KdDisconnectMethod::RPC_METHOD_NAME = "Kd.disconnect";
const std::string KdDisconnectMethod::RPC_SIGNATURE = "i:";

KdDisconnectMethod::KdDisconnectMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine_) :
		AbstractAsynchronousMethod(RPC_METHOD_NAME, RPC_SIGNATURE),
			pStateMachine(pStateMachine_) {
}

unsigned int KdDisconnectMethod::isActionCanceled() const {
	if (pStateMachine->getTargetStateInfo().stateId == Debugger::States::AttachedKernelState::THIS_STATE_ID) {
		return NO_CANCEL;
	}
	else {
		return INVALID_STATE;
	}
}

void KdDisconnectMethod::handleParameters(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
}

void KdDisconnectMethod::doAction() {
	pStateMachine->process_event(Debugger::Events::DisconnectEvent());
}

} /* namespace Methods */
} /* namespace Server */
