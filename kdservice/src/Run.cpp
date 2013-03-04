/*
 * Run.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#include "Command/Run.h"

#ifdef APP
#include "Command/RunApplication.h"
#else
#include "Command/RunWindowsService.h"
#endif
#include "Server/ServerBuilder.h"
#include "Service.h"
#include "IRunnable.h"

//#include <strsafe.h>
#include <iostream>
#include <boost/thread.hpp>

namespace Command {

IRunService* Run::pRunService = 0;

bool Run::run(const std::vector<std::wstring> &parameters) {
	if (pRunService) {
		return false;
	}
	pRunService = getRunService(parameters);
	pRunService->start();

	return true;
}

IRunService* Run::getRunService(const std::vector<std::wstring> &parameters) {
#ifdef APP
	IRunService* pRunApplication = new RunApplication();
	return pRunApplication;
#else
	IRunService* pRunApplication = new RunWindowsService();
	return pRunApplication;
#endif
}

void Run::wait() {
	pRunService->join();
}

} /* namespace Command */
