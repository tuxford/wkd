/*
 * KdAttachKernelMethod.cpp
 *
 *  Created on: Feb 15, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/Impl/KdAttachKernelMethod.h"
#include "Server/Methods/Methods.h"
#include "Debugger/Events/AttachKernelEvent.h"
#include "Debugger/States/ConnectedState.h"
#include "Debugger/Debugger.h"
#include "Service.h"

#include <boost/interprocess/sync/scoped_lock.hpp>

namespace Server {
namespace Methods {

const std::string KdAttachKernelMethod::METHOD_NAME = "Kd.attachKernel";
const std::string KdAttachKernelMethod::METHOD_SIGNATURE = "i:s";


KdAttachKernelMethod::KdAttachKernelMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine_) :
		AbstractAsynchronousMethod(METHOD_NAME, METHOD_SIGNATURE),
		pStateMachine(pStateMachine_){
}

unsigned int KdAttachKernelMethod::isActionCanceled() const {
	if (pStateMachine->getTargetStateInfo().stateId == Debugger::States::ConnectedState::THIS_STATE_ID) {
		return NO_CANCEL;
	}
	else {
		return INVALID_STATE;
	}
}

void KdAttachKernelMethod::handleParameters(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
		const char* pConnectParameters = 0;
		xmlrpc_decompose_value(pEnv, pParamArray, "(s)", &pConnectParameters);
		connectParameters = std::string(pConnectParameters);
}

void KdAttachKernelMethod::doAction() {
	pStateMachine->process_event(Debugger::Events::AttachKernelEvent(connectParameters));
}

} /* namespacrue Methods */
} /* namespace Server */
