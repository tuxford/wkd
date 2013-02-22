/*
 * OutputEvent.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: Roman Luchyshyn
 */

#include "Notifier/Events/OutputEvent.h"

namespace Notifier {
namespace Events {

OutputEvent::OutputEvent(const std::string& outputMessage) :
	message(outputMessage) {
}

std::string OutputEvent::getMessage() const {
	return message;
}

} /* namespace Events */
} /* namespace Notifier */
