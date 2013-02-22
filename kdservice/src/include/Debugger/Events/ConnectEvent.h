/*
 * ConnectEvent.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_Events_ConnectEvent_H_
#define Debugger_Events_ConnectEvent_H_

#include <boost/statechart/state_machine.hpp>

namespace Debugger {
namespace Events {

class ConnectEvent : public boost::statechart::event<ConnectEvent> {
};

}  // namespace Events
}  // namespace Debugger


#endif /* Debugger_Events_ConnectEvent_H_ */
