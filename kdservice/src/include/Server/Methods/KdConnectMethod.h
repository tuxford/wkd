/*
 * KdConnectMethod.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_KdConnectMethod_H_
#define Server_Methods_KdConnectMethod_H_

#include "Server/Methods/IConnectInterface.h"
#include "Server/Methods/AbstractMethod.h"

#include <xmlrpc-c/registry.hpp>

namespace Server {
namespace Methods {

class KdConnectMethod : public AbstractMethod
{
public:
	KdConnectMethod(IConnectInterface *pConnectInterface);

	virtual void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP);

private:
	static const std::string RPC_METHOD_NAME;
	static const std::string RPC_SIGNATURE;

	IConnectInterface *pConnectInterface;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_KdConnectMethod_H_ */
