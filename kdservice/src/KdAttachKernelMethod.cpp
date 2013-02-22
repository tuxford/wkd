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

namespace Server {
namespace Methods {

const std::string KdAttachKernelMethod::METHOD_NAME = "Kd.attachKernel";
const std::string KdAttachKernelMethod::METHOD_SIGNATURE = "i:s";


KdAttachKernelMethod::KdAttachKernelMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine) :
		AbstractMethod(METHOD_NAME, METHOD_SIGNATURE),
		pDebugStateMachine(pStateMachine) {
}

xmlrpc_value* KdAttachKernelMethod::execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
	try {

		const char* pConnectParameters = 0;
		xmlrpc_decompose_value(pEnv, pParamArray, "s", &pConnectParameters);

		pDebugStateMachine->process_event(Debugger::Events::AttachKernelEvent(std::string(pConnectParameters)));
		Service::LOGGER << log4cpp::Priority::DEBUG << "KdAttachKernelMethod::execute: connected successfully";
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

} /* namespacrue Methods */
} /* namespace Server */
