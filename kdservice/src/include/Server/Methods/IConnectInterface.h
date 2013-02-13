/*
 * IConnectInterface.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_IConnectInterface_H_
#define Server_Methods_IConnectInterface_H_

#include <string>

namespace Server {
namespace Methods {

class IConnectInterface
{
public:
	virtual ~IConnectInterface() {}

	virtual void connect(const std::string& parameters) = 0;
};

}  // namespace Methods
}  // namespace Server


#endif /* Server_Methods_IConnectInterface_H_ */
