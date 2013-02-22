/*
 * EventSerializer.h
 *
 *  Created on: Feb 19, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Notifier_EventSerializer_H_
#define Notifier_EventSerializer_H_

#include "Notifier/Events/ChangeStateEvent.h"

#include <string>

namespace Notifier {

class EventSerializer {
public:
	static std::string servialize(const Events::ChangeStateEvent& event);

private:
	static std::string boolToString(const std::string& valueId, bool value);
};

} /* namespace Notifier */
#endif /* Notifier_EventSerializer_H_ */
