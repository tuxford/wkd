/*
 * Methods.h
 *
 *  Created on: Feb 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_H_
#define Server_Methods_H_

#include "Core/Exception.h"

namespace Server {
namespace Methods {

static const int INTERNAL_ERROR = -1;

enum AsyncExecuteResult {
	SUCCESS = 0,
	FAIL = 1
};

typedef Core::Exception<int> ProxyException;

}  // namespace Methods
}  // namespace Server


#endif /* METHODS_H_ */
