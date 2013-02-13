/*
 * DebugRpcServer.cpp
 *
 *  Created on: Feb 7, 2013
 *      Author: rluchysh
 */

#include "Server/DebugRpcServer.h"

#include <sstream>
#include <iostream>
#include <exception>

namespace Server
{

const unsigned int DebugRpcServer::DEFAULT_PORT = 21605;
const unsigned long DebugRpcServer::WAIT_TIMEOUT_MS = 60000;

DebugRpcServer::DebugRpcServer(unsigned int srvPort, const Methods::MethodRegistry &registry) :
	port(srvPort),
	stopFlag(false),
	isRunFlag(false),
	threadHandle(INVALID_HANDLE_VALUE),
	pAbyssRpcServer(NULL),
	methodRegistry(registry)
{
}

bool DebugRpcServer::isRun()
{
	return isRunFlag;
}

void DebugRpcServer::start()
{
	if (isRun())
	{
		throw std::exception();//(std::string("Server already run"));
	}

	updatePortIfNeed();

	initRpcServer();

	threadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run, this, 0, NULL);
	if (threadHandle == NULL)
	{
		throw std::exception();//std::string("System didn't start thread"));
	}
}

void DebugRpcServer::stop()
{
	stopFlag = true;

	pAbyssRpcServer->terminate();

	if (WaitForSingleObject(threadHandle, WAIT_TIMEOUT_MS) == WAIT_OBJECT_0)
	{
		//TODO: implement force stop
	}
}

Methods::MethodRegistry DebugRpcServer::getMethodRegistry() const
{
	return methodRegistry;
}

void DebugRpcServer::initRpcMethodRegistry()
{
	for (Methods::MethodRegistry::AbstractMethodVector::const_iterator it = methodRegistry.getAllMethods().begin();
			it != methodRegistry.getAllMethods().end(); ++it)
	{
		xmlrpcRegistry.addMethod((*it)->getName(), *it);
	}
}

void DebugRpcServer::initRpcServer()
{
	initRpcMethodRegistry();

	pAbyssRpcServer = new xmlrpc_c::serverAbyss(xmlrpcRegistry, port);
	if (pAbyssRpcServer == NULL)
	{
		throw std::exception();//"Memory allocation for rpc server error");
	}
}

unsigned long DebugRpcServer::run(void* parameters)
{
	DebugRpcServer* pDebugRpcServer = (DebugRpcServer*)parameters;
	if (pDebugRpcServer == NULL)
	{
		pDebugRpcServer->isRunFlag = false;
		pDebugRpcServer->stopFlag = false;
		return 1;
	}

	pDebugRpcServer->isRunFlag = true;

	std::cout << "DebugRpcServer::run server is running" << std::endl;
	pDebugRpcServer->pAbyssRpcServer->run();
	std::cout << "DebugRpcServer::run server is stopped" << std::endl;

	pDebugRpcServer->isRunFlag = false;
	pDebugRpcServer->stopFlag = false;

	return NO_ERROR;
}

void DebugRpcServer::updatePortIfNeed()
{
	const unsigned int maxPortValue = 65535;
	if ((port == 0) || (port > maxPortValue))
	{
		port = DEFAULT_PORT;
	}
}

} /* namespace Server */
