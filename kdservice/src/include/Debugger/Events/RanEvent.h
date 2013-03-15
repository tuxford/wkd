/*
 * GoEvent.h
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_Events_GoEvent_H_
#define Debugger_Events_GoEvent_H_

#include <boost/statechart/state_machine.hpp>

namespace Debugger {
namespace Events {

class RanEvent : public boost::statechart::event<RanEvent> {
};

}  // namespace Events
}  // namespace Debugger


#endif /* Debugger_Events_GoEvent_H_ */
