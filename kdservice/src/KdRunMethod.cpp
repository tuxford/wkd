/*
 * KdRunMethod.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/Impl/KdRunMethod.h"
#include "Debugger/States/AttachedKernelState.h"
#include "Debugger/Debugger.h"

#include "Service.h"

namespace Server {
namespace Methods {

const std::string KdRunMethod::RPC_METHOD_NAME = "Kd.run";
const std::string KdRunMethod::RPC_SIGNATURE = "i:";

KdRunMethod::KdRunMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine_) :
	AbstractMethod(RPC_METHOD_NAME, RPC_SIGNATURE),
	pStateMachine(pStateMachine_) {
}

KdRunMethod::~KdRunMethod() {

}

xmlrpc_value* KdRunMethod::execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {

	Debugger::States::TargetStateInfo currentState = pStateMachine->getTargetStateInfo();
	if (currentState.stateId == Debugger::States::AttachedKernelState::THIS_STATE_ID) {
		try {
			pStateMachine->getDebugClient()->run();
			BOOST_LOG_TRIVIAL(debug) << "KdRunMethod::execute: success";
			return xmlrpc_build_value(pEnv, "i", SUCCESS);
		}
		catch(Debugger::DebugClientException &e) {
			BOOST_LOG_TRIVIAL(debug) << "KdRunMethod::execute: fail.";
			return xmlrpc_build_value(pEnv, "i", CLIENT_FAILED);
		}
		catch(...) {
			BOOST_LOG_TRIVIAL(debug) << "KdRunMethod::execute: fail. Unknown exception.";
			return xmlrpc_build_value(pEnv, "i", UNKNOWN_ERROR);
		}
	}
	BOOST_LOG_TRIVIAL(debug) << "KdRunMethod::execute: fail. Invalid state.";
	return xmlrpc_build_value(pEnv, "i", INVALID_STATE);
}

} /* namespace Methods */
} /* namespace Server */
