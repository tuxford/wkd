/*
 * KdConnect.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/KdConnectMethod.h"

#include <iostream>
#include <exception>

namespace Server {
namespace Methods {

const std::string KdConnectMethod::RPC_METHOD_NAME = "Kd.connect";
const std::string KdConnectMethod::RPC_SIGNATURE = "b:s";

KdConnectMethod::KdConnectMethod(IConnectInterface *pInterface) :
		AbstractMethod(RPC_METHOD_NAME, RPC_SIGNATURE),
		pConnectInterface(pInterface)
{
}

void KdConnectMethod::execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const pRetval)
{
	try
	{
		const std::string connectionParameters = paramList.getString(0);
		paramList.verifyEnd(1);

		pConnectInterface->connect(connectionParameters);

		*pRetval = xmlrpc_c::value_boolean(true);
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
		*pRetval = xmlrpc_c::value_boolean(false);
	}
}

} /* namespace Methods */
} /* namespace Server */
