/*
 * KdConnectMethod.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_KdConnectMethod_H_
#define Server_Methods_KdConnectMethod_H_

#include "Server/Methods/AbstractAsynchronousMethod.h"
#include "Debugger/StateMachine.h"

#include <xmlrpc-c/registry.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

namespace Server {
namespace Methods {

class KdConnectMethod: public AbstractAsynchronousMethod {
public:
	KdConnectMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine);

protected:
	virtual unsigned int isActionCanceled() const;
	virtual void handleParameters(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray);
	virtual void doAction();

private:
	static const std::string RPC_METHOD_NAME;
	static const std::string RPC_SIGNATURE;

	boost::shared_ptr<Debugger::StateMachine> pStateMachine;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_KdConnectMethod_H_ */
