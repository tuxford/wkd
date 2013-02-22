/*
 * DebugRpcServer.cpp
 *
 *  Created on: Feb 7, 2013
 *      Author: rluchysh
 */

#include "Server/DebugRpcServer.h"
#include "Service.h"

#include <xmlrpc-c/server_w32httpsys.h>

#include <sstream>
#include <iostream>
#include <exception>

namespace Server {

const unsigned long DebugRpcServer::WAIT_TIMEOUT_MS = 60000;

DebugRpcServer::DebugRpcServer(unsigned int srvPort, const Methods::MethodRegistry &registry) :
			port(srvPort),
			pAbyssRpcServer(NULL),
			methodRegistry(registry) {
}

void DebugRpcServer::start() {
	updatePortIfNeed();

	initRpcServer();
}

void DebugRpcServer::stop() {
//	pAbyssRpcServer->terminate();
}

static xmlrpc_value *
sample_add(xmlrpc_env * const env, xmlrpc_value * const param_array, void * const user_data) {
//    xmlrpc_int32 x, y, z;
	xmlrpc_value *pVal = xmlrpc_string_new(env, "");

	/* Parse our argument array. */

	/* Return our result. */
	return xmlrpc_build_value(env, "b", 1);
}

static void handleAuthorization(xmlrpc_env * envP, char * userid, char * password) {
}

void DebugRpcServer::operator()() {
	/*	if (pAbyssRpcServer == 0)
	 {
	 std::cout << "Critical: DebugRpcServer::operator() : pAbyssRpcServer not initialized" << std::endl;
	 return;
	 }
	 std::cout << "DebugRpcServer::operator() : start" << std::endl;
	 try
	 {
	 pAbyssRpcServer->processCall();

	 std::cout << "DebugRpcServer::operator() : !!!" << std::endl;
	 }
	 catch(...)
	 {
	 std::cout << "DebugRpcServer::operator() : fail" << std::endl;
	 }*/
	xmlrpc_server_httpsys_parms serverparm;
	memset(&serverparm, 0, sizeof(serverparm));
	xmlrpc_registry * registryP;
	xmlrpc_env env;

	xmlrpc_env_init(&env);
	Service::LOGGER << log4cpp::Priority::DEBUG << "DebugRpcServer::operator(): environment is initialized ";

	registryP = xmlrpc_registry_new(&env);
	Service::LOGGER << log4cpp::Priority::DEBUG << "DebugRpcServer::operator(): registry is initialized ";

	for (unsigned int i = 0; i < methodRegistry.getAllMethods().size(); ++i) {
		xmlrpc_method_info3 methodInfo = methodRegistry.getAllMethods()[i]->getMethodInfo();
		xmlrpc_registry_add_method3(&env, registryP, &methodInfo);
	}
	Service::LOGGER << log4cpp::Priority::DEBUG << "DebugRpcServer::operator(): methods are initialized ";

	serverparm.portNum = 21605;
	serverparm.useSSL = 0;
	serverparm.logLevel = 2;
	serverparm.logFile = "e:\\rpc.log";
	serverparm.authfn=&handleAuthorization;
	serverparm.registryP = registryP;
	Service::LOGGER << log4cpp::Priority::DEBUG << "DebugRpcServer::operator(): staring server";
	try	{
		xmlrpc_server_httpsys(&env, &serverparm, XMLRPC_HSSIZE(authfn));
	}
	catch(...) {
		Service::LOGGER << log4cpp::Priority::INFO << "DebugRpcServer::operator(): exception";
	}
	Service::LOGGER << log4cpp::Priority::INFO << "DebugRpcServer::operator(): server finished ";

}

void DebugRpcServer::initRpcMethodRegistry(xmlrpc_c::registry& xmlrpcRegistry) {
	for (Methods::MethodRegistry::AbstractMethodVector::const_iterator it = methodRegistry.getAllMethods().begin(); it != methodRegistry.getAllMethods().end(); ++it) {
//		xmlrpcRegistry.addMethod((*it)->getName(), *it);
	}
}

void DebugRpcServer::initRpcServer() {
	static xmlrpc_c::registry xmlrpcRegistry;
	initRpcMethodRegistry(xmlrpcRegistry);

//	xmlrpcRegistry.
	xmlrpc_c::serverCgi::constrOpt co;
	co.registryP(&xmlrpcRegistry);

	/*	pAbyssRpcServer = new xmlrpc_c::serverCgi(co);

	 if (pAbyssRpcServer == NULL)
	 {
	 throw std::exception("Memory allocation for rpc server error");
	 }*/
}

void DebugRpcServer::updatePortIfNeed() {
	const unsigned int maxPortValue = 65535;
	if ((port == 0) || (port > maxPortValue)) {
	}
}

} /* namespace Server */
