/*
 * Run.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Command_Run_H_
#define Command_Run_H_

#include "Server/IDebugServer.h"

#include <boost/shared_ptr.hpp>
#include <windows.h>
#include <string>
#include <vector>

namespace Command {

class Run {
public:
	static bool run(const std::vector<std::wstring> &parameters);

private:
	static const unsigned long KD_SERVICE_ERROR;

	static Run* pRun;

	HANDLE stopEvent;
	SERVICE_STATUS serviceStatus;
	SERVICE_STATUS_HANDLE serviceStatusHandle;
	unsigned long checkPoint;
	boost::shared_ptr<Server::IDebugServer> pDebugServer;
	std::vector<std::wstring> parameters;

	Run(const std::vector<std::wstring> &parameters);

	static void controlHandler(unsigned long controlCode);
	bool init();
	unsigned int getServerPortFromParameters() const;
	static void reportError(const std::string &function);
	void updateServiceStatus(unsigned long currentState, unsigned long exitCode, unsigned long waitHint);
	static void serviceEntry(int argc, LPSTR*);
	bool start();
	bool startAsApp();

};

} /* namespace Command */

#endif /* Command_Run_H_ */
