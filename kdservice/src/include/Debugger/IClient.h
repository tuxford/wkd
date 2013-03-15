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
	virtual void connect() = 0;
	virtual void attachKenel(const std::string& parameters) = 0;
	virtual void disconnect() = 0;
	virtual void setSourcePath(const std::string& sourcePath) = 0;
	virtual void setSymbolFilePath(const std::string& sourcePath) = 0;
	virtual void setDriverReplacemnetMap(const std::string& oldDriver, const std::string& newDriver) = 0;
	virtual void run() = 0;
};

}  // namespace Debugger


#endif /* Debugger_IClient_H_ */
