/*
 * DebugClientConnectProxy.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/DebugClientConnectProxy.h"

#include <stdexcept>

namespace Server {
namespace Methods {

DebugClientConnectProxy::DebugClientConnectProxy(Debugger::IClient* pClient) :
		pDebugClient(pClient)
{
}

void DebugClientConnectProxy::connect(const std::string& parameters)
{
	if (pDebugClient == 0)
	{
		throw std::runtime_error("Debug client is NULL");
	}

	pDebugClient->connect(parameters);
}

} /* namespace Methods */
} /* namespace Server */
