/*
 * ErrorEvent.h
 *
 *  Created on: Mar 7, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Notifier_Events_ErrorEvent_H_
#define Notifier_Events_ErrorEvent_H_

#include <string>

namespace Notifier {
namespace Events {

class ErrorEvent {
public:
	ErrorEvent(unsigned int errorCode, const std::string& module, const std::string& info);

	unsigned int getErrorCode() const;
	std::string getModule() const;
	std::string getInfo() const;

private:
	unsigned int errorCode;
	std::string module;
	std::string info;
};

} /* namespace Events */
} /* namespace Notifier */

#endif /* Notifier_Events_ErrorEvent_H_ */
