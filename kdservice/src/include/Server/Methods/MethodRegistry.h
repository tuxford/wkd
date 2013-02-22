/*
 * MethodRegistry.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_MethodRegistry_H_
#define Server_Methods_MethodRegistry_H_

#include "Server/Methods/AbstractMethod.h"

#include <vector>

namespace Server {
namespace Methods {

class MethodRegistry {
public:
	typedef std::vector<AbstractMethod*> AbstractMethodVector;

	MethodRegistry();
	const AbstractMethodVector& getAllMethods() const;
	void addMethod(AbstractMethod* method);

private:
	std::vector<AbstractMethod*> methods;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_MethodRegistry_H_ */
