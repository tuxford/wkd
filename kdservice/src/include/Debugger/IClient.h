/*
 * IClient.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_IClient_H_
#define Debugger_IClient_H_

#include "Core/Base.h"

#include <string>

namespace Debugger {

class IClient
{
public:
	virtual ~IClient() {}

	virtual void connect(const std::string& parameters) = 0;
	virtual void disconnect() = 0;
};

}  // namespace Debugger


#endif /* Debugger_IClient_H_ */
