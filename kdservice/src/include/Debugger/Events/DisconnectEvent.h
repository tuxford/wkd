/*
 * DisconnectEvent.h
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_Events_DisconnectEvent_H_
#define Debugger_Events_DisconnectEvent_H_

#include <boost/statechart/state_machine.hpp>

namespace Debugger {
namespace Events {

class DisconnectEvent : public boost::statechart::event<DisconnectEvent> {
};

}  // namespace Events
}  // namespace Debugger


#endif /* Debugger_Events_DisconnectEvent_H_ */
