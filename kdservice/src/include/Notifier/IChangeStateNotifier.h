/*
 * IChangeStateNotifier.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Notifier_IChangeStateNotifier_H_
#define Notifier_IChangeStateNotifier_H_

#include "Notifier/Events/ChangeStateEvent.h"

namespace Notifier {

class IChangeStateNotifier {
public:
	virtual ~IChangeStateNotifier() {}

	virtual void notify(const Events::ChangeStateEvent& event) = 0;
};

}  // namespace Notifier


#endif /* Notifier_IChangeStateNotifier_H_ */
