/*
 * EntryEvent.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_Events_EntryEvent_H_
#define Debugger_Events_EntryEvent_H_

#include <boost/statechart/state_machine.hpp>

namespace Debugger {
namespace Events {

class EntryEvent : public boost::statechart::event<EntryEvent> {
};

}  // namespace Events
}  // namespace Debugger

#endif /* Debugger_Events_EntryEvent_H_ */
