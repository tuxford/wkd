/*
 * ServerBuilder.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_ServerBuilder_H_
#define Server_ServerBuilder_H_

#include "Server/Methods/MethodRegistry.h"

namespace Server {

class DebugRpcServer;

class ServerBuilder
{
public:
	static DebugRpcServer* build(const unsigned int& port);

private:
	static void initMethodRegistry(Methods::MethodRegistry &methodRegistry);
};

} /* namespace Server */

#endif /* Server_ServerBuilder_H_ */
