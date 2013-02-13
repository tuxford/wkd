/*
 * KdClient.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_KdClient_H_
#define Debugger_KdClient_H_

#include "Debugger/IClient.h"

namespace Debugger {

class KdClient: public IClient
{
public:
	KdClient();
	virtual ~KdClient() {};

	virtual void connect(const std::string& parameters);
	virtual void disconnect();

private:
	Core::DebugClientInterface* pDebugClient;
	Core::DebugControlInterface* pDebugControl;

	void createDebugClient();
	void createDebugControl();
	void attachKernel(const std::string& parameters);
	void waitForEvent();
};

} /* namespace Debugger */

#endif /* Debugger_KdClient_H_ */
