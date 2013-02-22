/*
 * ServerBuilder.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_ServerBuilder_H_
#define Server_ServerBuilder_H_

#include "Server/IDebugServer.h"
#include "Server/Methods/MethodRegistry.h"
#include "Debugger/StateMachine.h"

#include <boost/shared_ptr.hpp>

namespace Server {

class DebugRpcServer;

class ServerBuilder {
public:
	static const unsigned int DEFAULT_PORT;

	static boost::shared_ptr<IDebugServer> build(const unsigned int& port);

private:
	static void initMethodRegistry(Methods::MethodRegistry &methodRegistry, boost::shared_ptr<Debugger::StateMachine> pDebuggerStateMachine);
	static boost::shared_ptr<Debugger::StateMachine> buildDebuggerStateMachine();
};

} /* namespace Server */

#endif /* Server_ServerBuilder_H_ */
