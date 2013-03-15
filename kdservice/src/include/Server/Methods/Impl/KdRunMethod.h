/*
 * KdRunMethod.h
 *
 *  Created on: Mar 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_KdRunMethod_H_
#define Server_Methods_KdRunMethod_H_

#include "Server/Methods/AbstractMethod.h"
#include "Debugger/StateMachine.h"

namespace Server {
namespace Methods {

class KdRunMethod: public AbstractMethod {
public:
	enum SetSourcePathResult {
		SUCCESS = 0,
		INVALID_STATE = 1,
		CLIENT_FAILED = 2,

		UNKNOWN_ERROR = -1
	};

	KdRunMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine);
	virtual ~KdRunMethod();

	virtual xmlrpc_value* execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray);

private:
	static const std::string RPC_METHOD_NAME;
	static const std::string RPC_SIGNATURE;
	boost::shared_ptr<Debugger::StateMachine> pStateMachine;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_KdRunMethod_H_ */
