/*
 * ErrorEvent.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: rluchysh
 */

#include "Notifier/Events/ErrorEvent.h"

namespace Notifier {
namespace Events {

ErrorEvent::ErrorEvent(unsigned int code_, const std::string& module_, const std::string& info_) :
		errorCode(code_),
		module(module_),
		info(info_) {
}

unsigned int ErrorEvent::getErrorCode() const {
	return errorCode;
}

std::string ErrorEvent::getModule() const {
	return module;
}

std::string ErrorEvent::getInfo() const {
	return info;
}

} /* namespace Events */
} /* namespace Notifier */
