/*
 * ServerBuilder.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/ServerBuilder.h"
#include "Server/IDebugServer.h"
#include "Server/DebugRpcServer.h"
#include "Server/Methods/Impl/KdConnectMethod.h"
#include "Debugger/KdClient.h"
#include "Debugger/Events/EntryEvent.h"
#include "Debugger/States/InitialState.h"

#include <boost/shared_ptr.hpp>

namespace Server {

const unsigned int ServerBuilder::DEFAULT_PORT = 21605;

boost::shared_ptr<IDebugServer> ServerBuilder::build(const unsigned int& port) {

	Methods::MethodRegistry methodsRegistry;

	boost::shared_ptr<Debugger::StateMachine> pStateMachine = buildDebuggerStateMachine();

	initMethodRegistry(methodsRegistry, pStateMachine);

	boost::shared_ptr<IDebugServer> result(new DebugRpcServer(port, methodsRegistry));

	return result;
}

void ServerBuilder::initMethodRegistry(Methods::MethodRegistry &methodRegistry, boost::shared_ptr<Debugger::StateMachine> pDebuggerStateMachine) {

	methodRegistry.addMethod(new Methods::KdConnectMethod(pDebuggerStateMachine));

}

boost::shared_ptr<Debugger::StateMachine> ServerBuilder::buildDebuggerStateMachine() {
	boost::shared_ptr<Debugger::KdClient> pDebugClient(new Debugger::KdClient());

	boost::shared_ptr<Debugger::StateMachine> pDebuggerStateMachine(new Debugger::StateMachine(pDebugClient));

	pDebugClient->setTargetStateMachine(pDebuggerStateMachine.get());

	pDebuggerStateMachine->initiate();
	pDebuggerStateMachine->process_event(Debugger::Events::EntryEvent());

	return pDebuggerStateMachine;
}

} /* namespace Server */
