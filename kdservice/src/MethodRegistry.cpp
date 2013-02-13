/*
 * MethodRegistry.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/MethodRegistry.h"

namespace Server {
namespace Methods {

MethodRegistry::MethodRegistry() {
}

const MethodRegistry::AbstractMethodVector& MethodRegistry::getAllMethods() const
{
	return methods;
}

void MethodRegistry::addMethod(AbstractMethod* method)
{
	methods.push_back(method);
}

} /* namespace Methods */
} /* namespace Server */
