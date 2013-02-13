/*
 * AbstractMethod.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/AbstractMethod.h"

namespace Server {
namespace Methods {

AbstractMethod::AbstractMethod(const std::string& methodName, const std::string& methodSignature) :
		name(methodName)
{
	this->_signature = methodSignature;
}

AbstractMethod::~AbstractMethod()
{
}

std::string AbstractMethod::getName() const
{
	return name;
}

} /* namespace Methods */
} /* namespace Server */
