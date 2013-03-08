/*
 * KdAttachKernelMethod.cpp
 *
 *  Created on: Feb 15, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/Impl/KdAttachKernelMethod.h"
#include "Server/Methods/Methods.h"
#include "Debugger/Events/AttachKernelEvent.h"
#include "Debugger/Debugger.h"
#include "Service.h"

#include <boost/interprocess/sync/scoped_lock.hpp>

namespace Server {
namespace Methods {

const std::string KdAttachKernelMethod::METHOD_NAME = "Kd.attachKernel";
const std::string KdAttachKernelMethod::METHOD_SIGNATURE = "i:s";


KdAttachKernelMethod::KdAttachKernelMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine) :
		AbstractMethod(METHOD_NAME, METHOD_SIGNATURE),
		pDebugStateMachine(pStateMachine) {
}

xmlrpc_value* KdAttachKernelMethod::execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
	if (pExecutionThread.get()) {
		Service::LOGGER << log4cpp::Priority::WARN << "KdAttachKernelMethod::execute: thread is initialized. ";
	}

	boost::interprocess::scoped_lock<boost::mutex> lock(executionMutex);

	try {

		const char* pConnectParameters = 0;
		xmlrpc_decompose_value(pEnv, pParamArray, "(s)", &pConnectParameters);
		connectParameters = std::string(pConnectParameters);
		boost::shared_ptr<boost::thread> pThread(new boost::thread(boost::bind(&KdAttachKernelMethod::operator(), this)));
		pExecutionThread = pThread;
		return xmlrpc_build_value(pEnv, "i", 0);

	}
	catch (Debugger::DebugClientException &e) {
		Service::LOGGER << log4cpp::Priority::ERROR << "KdAttachKernelMethod::execute: connect exception: " << e.getMessage();
		return xmlrpc_build_value(pEnv, "i", e.getErrorCode());
	}
	catch (ProxyException &e) {
		Service::LOGGER << log4cpp::Priority::ERROR << "KdAttachKernelMethod::execute: proxy exception: " << e.getMessage();
		return xmlrpc_build_value(pEnv, "i", e.getErrorCode());
	}
	catch (...) {
		Service::LOGGER << log4cpp::Priority::ERROR << "KdAttachKernelMethod::execute: unknown exception";
		return xmlrpc_build_value(pEnv, "i", INTERNAL_ERROR);
	}
}

void KdAttachKernelMethod::operator()() {
	boost::interprocess::scoped_lock<boost::mutex> lock(executionMutex);
	pDebugStateMachine->process_event(Debugger::Events::AttachKernelEvent(connectParameters));
}

} /* namespacrue Methods */
} /* namespace Server */
