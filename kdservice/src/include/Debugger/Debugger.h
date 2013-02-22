/*
 * Debugger.h
 *
 *  Created on: Feb 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_H_
#define Debugger_H_

#include "Core/Exception.h"

namespace Debugger {

static const int INTERNAL_ERROR = -1;

enum HandleResult {
	SUCCESS = 0,
	ALREADY_INITILIZED = 1,
	ATTACH_KERNEL_ERROR = 2,
	TARGET_UNAVAILABLE = 3,
	ALREADY_ATTACHED_KERNEL = 4,
	UNEXPECTED_ERROR = INTERNAL_ERROR
};

typedef Core::Exception<HandleResult> DebugClientException;

}  // namespace Debugger


#endif /* Debugger_H_ */
