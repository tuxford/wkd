/*
 * KdConnectMethod.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_KdConnectMethod_H_
#define Server_Methods_KdConnectMethod_H_

#include "Server/Methods/AbstractMethod.h"
#include "Debugger/StateMachine.h"

#include <xmlrpc-c/registry.hpp>

namespace Server {
namespace Methods {

class KdConnectMethod: public AbstractMethod {
public:
	KdConnectMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine);

	xmlrpc_value* execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray);

private:
	static const std::string RPC_METHOD_NAME;
	static const std::string RPC_SIGNATURE;

	boost::shared_ptr<Debugger::StateMachine> pDebugStateMachine;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_KdConnectMethod_H_ */
