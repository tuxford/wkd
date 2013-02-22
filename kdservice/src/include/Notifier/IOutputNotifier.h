/*
 * IOutputNotifier.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Notifier_IOutputNotifier_H_
#define Notifier_IOutputNotifier_H_

#include "Notifier/Events/OutputEvent.h"

namespace Notifier {

class IOutputNotifier {
public:
	virtual ~IOutputNotifier() {}

	virtual void notify(const Events::OutputEvent& event) = 0;
};

}  // namespace Notifier


#endif /* Notifier_IOutputNotifier_H_ */
