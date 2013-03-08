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

#include <boost/interprocess/sync/scoped_lock.hpp>

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

KdConnectMethod::~KdConnectMethod() {
	Service::LOGGER << log4cpp::Priority::WARN << "KdConnectMethod::~KdConnectMethod: ";
	if (pExecutionThread.get()) {
		pExecutionThread->join();
	}
}

xmlrpc_value* KdConnectMethod::execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
	if (pExecutionThread.get()) {
		Service::LOGGER << log4cpp::Priority::WARN << "KdConnectMethod::execute: thread is initialized. ";
	}

	boost::interprocess::scoped_lock<boost::mutex> lock(executionMutex);

	try {
		Service::LOGGER << log4cpp::Priority::DEBUG << "KdConnectMethod::execute: connecting in process";
		boost::shared_ptr<boost::thread> pThread(new boost::thread(boost::bind(&KdConnectMethod::operator(), this)));
		pExecutionThread = pThread;
		Service::LOGGER << log4cpp::Priority::DEBUG << "KdConnectMethod::execute: 0";
		return xmlrpc_build_value(pEnv, "i", SUCCESS);

	}
	catch (...) {
		Service::LOGGER << log4cpp::Priority::ERROR << "KdConnectMethod::execute: unknown exception";
		return xmlrpc_build_value(pEnv, "i", INTERNAL_ERROR);
	}

}

void KdConnectMethod::operator()() {
	boost::interprocess::scoped_lock<boost::mutex> lock(executionMutex);
	pDebugStateMachine->process_event(Debugger::Events::ConnectEvent());
}

} /* namespace Methods */
} /* namespace Server */
