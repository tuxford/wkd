/*
 * AbstractMethod.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_AbstractMethod_H_
#define Server_Methods_AbstractMethod_H_

#include <string>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>

namespace Server {
namespace Methods {

class AbstractMethod {
public:
	AbstractMethod(const std::string& name, const std::string& signature);
	virtual ~AbstractMethod();

	xmlrpc_method_info3 getMethodInfo();
	std::string getName() const;
	std::string getSignature() const;

protected:
	virtual xmlrpc_value* execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) = 0;

private:
	const std::string name;
	const std::string signature;

	static xmlrpc_value* executeMethod(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray, void* const pMethod, void* const pCallInfo);
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_AbstractMethod_H_ */
