/*
 * KdConnect.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/Impl/KdConnectMethod.h"
#include "Server/Methods/Methods.h"
#include "Debugger/Debugger.h"
#include "Debugger/Events/ConnectEvent.h"
#include "Service.h"

#include <iostream>
#include <exception>

namespace Server {
namespace Methods {

const std::string KdConnectMethod::RPC_METHOD_NAME = "Kd.connect";
const std::string KdConnectMethod::RPC_SIGNATURE = "i:";

KdConnectMethod::KdConnectMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine) :
			AbstractMethod(RPC_METHOD_NAME, RPC_SIGNATURE),
			pDebugStateMachine(pStateMachine) {
}

xmlrpc_value* KdConnectMethod::execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {

	try {
		Service::LOGGER << log4cpp::Priority::DEBUG << "KdConnectMethod::execute: connecting in process";
		pDebugStateMachine->process_event(Debugger::Events::ConnectEvent());
		return xmlrpc_build_value(pEnv, "i", AsyncExecuteResult::SUCCESS);

	}
	catch (...) {
		Service::LOGGER << log4cpp::Priority::ERROR << "KdConnectMethod::execute: unknown exception";
		return xmlrpc_build_value(pEnv, "i", INTERNAL_ERROR);
	}

}

} /* namespace Methods */
} /* namespace Server */
