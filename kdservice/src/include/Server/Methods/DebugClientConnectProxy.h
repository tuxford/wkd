/*
 * DebugClientConnectProxy.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_DebugClientConnectProxy_H_
#define Server_Methods_DebugClientConnectProxy_H_

#include "IConnectInterface.h"
#include "Debugger/IClient.h"

namespace Server {
namespace Methods {

class DebugClientConnectProxy: public IConnectInterface
{
public:
	DebugClientConnectProxy(Debugger::IClient* pDebugClient);

	virtual void connect(const std::string& parameters);

private:
	Debugger::IClient* pDebugClient;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_DebugClientConnectProxy_H_ */
