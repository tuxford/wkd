/*
 * DebugRpcServer.h
 *
 *  Created on: Feb 7, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_DebugRpcServer_H_
#define Server_DebugRpcServer_H_

#include "Server/Methods/MethodRegistry.h"
#include "Server/IDebugServer.h"
#include "IRunnable.h"

#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_cgi.hpp>
#include <vector>

namespace Server {

class DebugRpcServer: public IDebugServer, public IRunnable {
public:
	DebugRpcServer(unsigned int port, const Methods::MethodRegistry &methodRegistry);

	virtual void start();
	virtual void stop();
	virtual void operator()();

private:
	static const unsigned long WAIT_TIMEOUT_MS;

	unsigned int port;
	xmlrpc_c::serverCgi *pAbyssRpcServer;
	Methods::MethodRegistry methodRegistry;

	void initRpcMethodRegistry(xmlrpc_c::registry& xmlrpcRegistry);
	void initRpcServer();
	void updatePortIfNeed();

};

} /* namespace Server */

#endif /* Server_DebugRpcServer_H_ */
