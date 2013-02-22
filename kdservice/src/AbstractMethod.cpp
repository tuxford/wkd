/*
 * AbstractMethod.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/AbstractMethod.h"

#include <iostream>

namespace Server {
namespace Methods {

AbstractMethod::AbstractMethod(const std::string& methodName, const std::string& methodSignature) :
			name(methodName),
			signature(methodSignature) {
}

AbstractMethod::~AbstractMethod() {
}

xmlrpc_method_info3 AbstractMethod::getMethodInfo() {

	xmlrpc_method_info3 methodInfo;
	methodInfo.methodName = name.c_str();
	methodInfo.signatureString = signature.c_str();
	methodInfo.help = 0;
	methodInfo.methodFunction = &AbstractMethod::executeMethod;
	methodInfo.serverInfo = this;
	methodInfo.stackSize = 0;

	return methodInfo;
}

std::string AbstractMethod::getName() const {
	return name;
}

std::string AbstractMethod::getSignature() const {
	return signature;
}

xmlrpc_value* AbstractMethod::executeMethod(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray, void* const pMethod, void* const pCallInfo) {

	AbstractMethod* pAbstractMethod = static_cast<AbstractMethod*>(pMethod);
	xmlrpc_value* result = pAbstractMethod->execute(pEnv, pParamArray);

	return result;
}

} /* namespace Methods */
} /* namespace Server */
