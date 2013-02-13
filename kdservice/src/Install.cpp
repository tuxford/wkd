/*
 * Install.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: rluchysh
 */

#include "Command/Install.h"
#include "Service.h"

#include <windows.h>

#include <iostream>

namespace Command
{

const std::wstring Install::COMMAND = L"install";

bool Install::install()
{
	const int max_path_size = 1024;
	char path[max_path_size];
	if (!GetModuleFileNameA(NULL, path, max_path_size))
	{
		std::cout << "Can't install service. Error " << GetLastError() << std::endl;
		return false;
	}

	SC_HANDLE schScManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schScManager == NULL)
	{
		std::cout << "Can't open SCManager. Error " << GetLastError() << std::endl;
		return false;
	}

	SC_HANDLE schService = CreateService(
			schScManager,
			Service::NAME.c_str(),
			Service::NAME.c_str(),
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			path,
			NULL, NULL, NULL, NULL, NULL
			);

	if (schService == NULL)
	{
		std::cout << "Can't install service. Error " << GetLastError() << std::endl;
		CloseServiceHandle(schService);
		return false;

	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schScManager);

	return true;
}

} /* namespace Command */
