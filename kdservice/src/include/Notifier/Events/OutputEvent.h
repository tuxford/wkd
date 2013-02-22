/*
 * OutputEvent.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Notifier_Events_OutputEvent_H_
#define Notifier_Events_OutputEvent_H_

#include <string>

namespace Notifier {
namespace Events {

class OutputEvent {
public:
	OutputEvent(const std::string& message);

	std::string getMessage() const;

private:
	const std::string message;
};

} /* namespace Events */
} /* namespace Notifier */

#endif /* Notifier_Events_OutputEvent_H_ */
