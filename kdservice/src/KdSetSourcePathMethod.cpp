/*
 * KdSetSourcePathMethod.cpp
 *
 *  Created on: Mar 13, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/Impl/KdSetSourcePathMethod.h"
#include "Debugger/States/AttachedKernelState.h"
#include "Debugger/Debugger.h"

#include "Service.h"

namespace Server {
namespace Methods {

const std::string KdSetSourcePathMethod::RPC_METHOD_NAME = "Kd.setSourcePath";
const std::string KdSetSourcePathMethod::RPC_SIGNATURE = "i:s";

KdSetSourcePathMethod::KdSetSourcePathMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine_) :
	AbstractMethod(RPC_METHOD_NAME, RPC_SIGNATURE),
	pStateMachine(pStateMachine_) {
}

KdSetSourcePathMethod::~KdSetSourcePathMethod() {

}

xmlrpc_value* KdSetSourcePathMethod::execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
	const char* pSourcePath = 0;
	xmlrpc_decompose_value(pEnv, pParamArray, "(s)", &pSourcePath);
	std::string  sourcePath = std::string(pSourcePath);

	Debugger::States::TargetStateInfo currentState = pStateMachine->getTargetStateInfo();
	if (currentState.stateId == Debugger::States::AttachedKernelState::THIS_STATE_ID) {
		try {
			pStateMachine->getDebugClient()->setSourcePath(sourcePath);
			BOOST_LOG_TRIVIAL(debug) << "KdSetSourcePathMethod::execute: success";
			return xmlrpc_build_value(pEnv, "i", SUCCESS);
		}
		catch(Debugger::DebugClientException &e) {
			BOOST_LOG_TRIVIAL(debug) << "KdSetSourcePathMethod::execute: fail.";
			return xmlrpc_build_value(pEnv, "i", CLIENT_FAILED);
		}
		catch(...) {
			BOOST_LOG_TRIVIAL(debug) << "KdSetSourcePathMethod::execute: fail. Unknown exception.";
			return xmlrpc_build_value(pEnv, "i", UNKNOWN_ERROR);
		}
	}
	BOOST_LOG_TRIVIAL(debug) << "KdSetSourcePathMethod::execute: fail. Invalid state.";
	return xmlrpc_build_value(pEnv, "i", INVALID_STATE);
}

} /* namespace Methods */
} /* namespace Server */
