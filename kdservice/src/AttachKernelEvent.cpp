/*
 * AttachKernelEvent.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/Events/AttachKernelEvent.h"

namespace Debugger {
namespace Events {

AttachKernelEvent::AttachKernelEvent(const std::string& attachParams) :
	attachKernelParams(attachParams) {
}

std::string AttachKernelEvent::getAttachKernelParams() const {
	return attachKernelParams;
}

}  // namespace Events
}  // namespace Debugger



