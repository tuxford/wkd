/*
 * ServerBuilder.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/ServerBuilder.h"
#include "Server/DebugRpcServer.h"
#include "Server/Methods/KdConnectMethod.h"
#include "Server/Methods/DebugClientConnectProxy.h"
#include "Debugger/KdClient.h"

namespace Server {

DebugRpcServer* ServerBuilder::build(const unsigned int& port)
{
	Methods::MethodRegistry methodsRegistry;
	initMethodRegistry(methodsRegistry);

	DebugRpcServer* result = new DebugRpcServer(port, methodsRegistry);

	return result;
}

void ServerBuilder::initMethodRegistry(Methods::MethodRegistry &methodRegistry)
{
	Debugger::IClient *pDebugClient = new Debugger::KdClient();
	methodRegistry.addMethod(new Methods::KdConnectMethod(new Methods::DebugClientConnectProxy(pDebugClient)));
}

} /* namespace Server */
