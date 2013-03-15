/*
 * KdSetSymbolFilePathMethod.cpp
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/Impl/KdSetSymbolFilePathMethod.h"
#include "Debugger/States/AttachedKernelState.h"
#include "Debugger/Debugger.h"

#include "Service.h"

namespace Server {
namespace Methods {

const std::string KdSetSymbolFilePathMethod::RPC_METHOD_NAME = "Kd.setSymbolFilePath";
const std::string KdSetSymbolFilePathMethod::RPC_SIGNATURE = "i:s";

KdSetSymbolFilePathMethod::KdSetSymbolFilePathMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine_) :
	AbstractMethod(RPC_METHOD_NAME, RPC_SIGNATURE),
	pStateMachine(pStateMachine_) {
}

KdSetSymbolFilePathMethod::~KdSetSymbolFilePathMethod() {

}

xmlrpc_value* KdSetSymbolFilePathMethod::execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
	const char* pSymbolPath = 0;
	xmlrpc_decompose_value(pEnv, pParamArray, "(s)", &pSymbolPath);
	std::string  symbolFilePath = std::string(pSymbolPath);

	Debugger::States::TargetStateInfo currentState = pStateMachine->getTargetStateInfo();
	if (currentState.stateId == Debugger::States::AttachedKernelState::THIS_STATE_ID) {
		try {
			pStateMachine->getDebugClient()->setSymbolFilePath(symbolFilePath);
			Service::LOGGER << log4cpp::Priority::DEBUG << "KdSetSymbolFilePathMethod::execute: success";
			return xmlrpc_build_value(pEnv, "i", SUCCESS);
		}
		catch(Debugger::DebugClientException &e) {
			Service::LOGGER << log4cpp::Priority::DEBUG << "KdSetSymbolFilePathMethod::execute: fail.";
			return xmlrpc_build_value(pEnv, "i", CLIENT_FAILED);
		}
		catch(...) {
			Service::LOGGER << log4cpp::Priority::DEBUG << "KdSetSymbolFilePathMethod::execute: fail. Unknown exception.";
			return xmlrpc_build_value(pEnv, "i", UNKNOWN_ERROR);
		}
	}
	Service::LOGGER << log4cpp::Priority::DEBUG << "KdSetSymbolFilePathMethod::execute: fail. Invalid state.";
	return xmlrpc_build_value(pEnv, "i", INVALID_STATE);
}

} /* namespace Methods */
} /* namespace Server */
