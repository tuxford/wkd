/*
 * DebugRpcServer.h
 *
 *  Created on: Feb 7, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_DebugRpcServer_H_
#define Server_DebugRpcServer_H_

#include "Methods/MethodRegistry.h"

#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

#include <vector>

namespace Server
{

class DebugRpcServer
{
public:
	static const unsigned int DEFAULT_PORT;

	DebugRpcServer(unsigned int port, const Methods::MethodRegistry &methodRegistry);

	bool isRun();
	void start(); 	/* Method registry must be filled before server start */
	void stop();

private:
	static const unsigned long WAIT_TIMEOUT_MS;

	unsigned int port;
	bool stopFlag;
	bool isRunFlag;
	HANDLE threadHandle;

	xmlrpc_c::serverAbyss *pAbyssRpcServer;
	xmlrpc_c::registry xmlrpcRegistry;
	Methods::MethodRegistry methodRegistry;

	Methods::MethodRegistry getMethodRegistry() const;
	void initRpcMethodRegistry();
	void initRpcServer();
	static unsigned long run(void* parameters);
	void updatePortIfNeed();

};

} /* namespace Server */

#endif /* Server_DebugRpcServer_H_ */
