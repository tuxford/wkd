/*
 * Install.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: rluchysh
 */

#include "Command/Install.h"
#include "Service.h"

#ifndef SIM
#include <windows.h>
#endif

#include <iostream>

namespace Command {

const std::wstring Install::COMMAND = L"install";

bool Install::install() {
#ifndef SIM
	const int max_path_size = 1024;
	char path[max_path_size];
	if (!GetModuleFileNameA(NULL, path, max_path_size)) {
		Service::LOGGER << log4cpp::Priority::CRIT << "Installation failed. Can't obtain service. Error: " << GetLastError();
		return false;
	}

	SC_HANDLE schScManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schScManager == NULL) {
		Service::LOGGER << log4cpp::Priority::CRIT << "Installation failed. Can't open SCManager. Error: " << GetLastError();
		return false;
	}

	SC_HANDLE schService = CreateService(schScManager, Service::NAME.c_str(), Service::NAME.c_str(), SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, path,
			NULL, NULL, NULL, NULL, NULL);

	if (schService == NULL) {
		Service::LOGGER << log4cpp::Priority::CRIT << "Can't install service. Error " << GetLastError();
		CloseServiceHandle(schService);
		return false;

	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schScManager);
#endif
	return true;
}

} /* namespace Command */
