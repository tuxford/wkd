/*
 * AttachedKernelState.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/States/AttachedKernelState.h"
#include "Service.h"

namespace Debugger {
namespace States {

const StateId AttachedKernelState::THIS_STATE_ID = "attachedKernel";

AttachedKernelState::AttachedKernelState() {
	Service::LOGGER << log4cpp::Priority::DEBUG << "AttachedKernelState::AttachedKernelState";
}

AttachedKernelState::~AttachedKernelState() {
}


} /* namespace States */
} /* namespace Debugger */
