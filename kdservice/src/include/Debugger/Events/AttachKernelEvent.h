/*
 * AttachKernelEvent.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_Events_AttachKernelEvent_H_
#define Debugger_Events_AttachKernelEvent_H_

#include <boost/statechart/state_machine.hpp>

namespace Debugger {
namespace Events {

class AttachKernelEvent : public boost::statechart::event<AttachKernelEvent> {

public:
	AttachKernelEvent(const std::string& params);

	std::string getAttachKernelParams() const;

private:
	const std::string attachKernelParams;
};

}  // namespace Events
}  // namespace Debugger


#endif /* Debugger_Events_AttachKernelEvent_H_ */
