/*
 * IClient.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_IClient_H_
#define Debugger_IClient_H_

#include "Core/Base.h"
#include "Debugger/States/TargetStateInfo.h"

#include <string>

namespace Debugger {

class IClient
{
public:
	virtual ~IClient() {}

	virtual const States::TargetStateInfo getTargetStateInfo() const = 0;
	virtual int connect() = 0;
	virtual int attachKenel(const std::string& parameters) = 0;
	virtual int disconnect() = 0;
};

}  // namespace Debugger


#endif /* Debugger_IClient_H_ */
