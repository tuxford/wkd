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

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

namespace Server {
namespace Methods {

class KdConnectMethod: public AbstractMethod {
public:
	KdConnectMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine);
	~KdConnectMethod();

	xmlrpc_value* execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray);

	void operator()();
private:
	static const std::string RPC_METHOD_NAME;
	static const std::string RPC_SIGNATURE;

	boost::shared_ptr<Debugger::StateMachine> pDebugStateMachine;
	boost::mutex executionMutex;
	boost::shared_ptr<boost::thread> pExecutionThread;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_KdConnectMethod_H_ */
