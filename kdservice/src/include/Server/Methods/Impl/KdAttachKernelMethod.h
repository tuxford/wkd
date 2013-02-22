/*
 * KdAttachKernelMethod.h
 *
 *  Created on: Feb 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_KdAttachKernelMethod_H_
#define Server_Methods_KdAttachKernelMethod_H_

#include "Server/Methods/AbstractMethod.h"
#include "Debugger/StateMachine.h"

#include <boost/shared_ptr.hpp>

namespace Server {
namespace Methods {

class KdAttachKernelMethod: public AbstractMethod {

public:
	KdAttachKernelMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine);

	virtual xmlrpc_value* execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray);

private:
	static const std::string METHOD_NAME;
	static const std::string METHOD_SIGNATURE;

	boost::shared_ptr<Debugger::StateMachine> pDebugStateMachine;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_KdAttachKernelMethod_H_ */
