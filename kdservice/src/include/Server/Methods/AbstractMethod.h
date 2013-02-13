/*
 * AbstractMethod.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_AbstractMethod_H_
#define Server_Methods_AbstractMethod_H_

#include <xmlrpc-c/registry.hpp>

namespace Server {
namespace Methods {

class AbstractMethod: public xmlrpc_c::method
{
public:
	AbstractMethod(const std::string& name, const std::string& signature);
	virtual ~AbstractMethod();

	std::string getName() const;

private:
	const std::string name;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_AbstractMethod_H_ */
