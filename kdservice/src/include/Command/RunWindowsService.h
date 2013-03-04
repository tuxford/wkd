/*
 * RunWindowsService.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Command_RunWindowsService_H_
#define Command_RunWindowsService_H_

#include "Command/IRunService.h"
#include "Server/IDebugServer.h"

#include <windows.h>

#include <boost/shared_array.hpp>

#include <vector>

namespace Command {

class RunWindowsService: public IRunService {
public:
	RunWindowsService();

	virtual void start();
	virtual void stop();
	virtual void join();

private:
	static const unsigned long KD_SERVICE_ERROR;

	static RunWindowsService* pRunWindowsService;


	HANDLE stopEvent;
	SERVICE_STATUS serviceStatus;
	SERVICE_STATUS_HANDLE serviceStatusHandle;
	unsigned long checkPoint;
	boost::shared_ptr<Server::IDebugServer> pDebugServer;
	std::vector<std::wstring> parameters;

	static void controlHandler(unsigned long controlCode);
	bool init();
	unsigned int getServerPortFromParameters() const;
	static void reportError(const std::string &function);
	void updateServiceStatus(unsigned long currentState, unsigned long exitCode, unsigned long waitHint);
	static void serviceEntry(int argc, LPSTR*);

};

} /* namespace Command */

#endif /* Command_RunWindowsService_H_ */
