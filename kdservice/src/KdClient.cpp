/*
 * KdClient.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/KdClient.h"

#include <exception>
#include <iostream>

namespace Debugger {

KdClient::KdClient() :
		pDebugClient(0),
		pDebugControl(0)
{
}

void KdClient::connect(const std::string& parameters)
{
	createDebugClient();
	createDebugControl();
	attachKernel(parameters);
}

void KdClient::disconnect()
{
	if (pDebugControl)
	{
		pDebugControl->Release();
		pDebugControl = 0;
	}
	else
	{
		throw std::exception("Attempt to destroy uninitialized object \"pDebugControl\"");
	}

	if (pDebugClient != 0)
	{
		pDebugClient->EndSession(DEBUG_END_ACTIVE_DETACH);
		pDebugClient->Release();
		pDebugClient = 0;
	}
	else
	{
		throw std::exception("Attempt to destroy uninitialized object \"pDebugClient\"");
	}
}

void KdClient::createDebugClient()
{
	HRESULT debugCreateStatus = ::DebugCreate(__uuidof(IDebugClient), (void**)&pDebugClient);
	if (debugCreateStatus != S_OK)
	{
		throw std::exception("Cann't initialize debug client. DebugCreate failed.");
	}
}

void KdClient::createDebugControl()
{
	HRESULT queryDebugControlInterfaceStatus = pDebugClient->QueryInterface(__uuidof(IDebugControl), (void**)&pDebugControl);
	if (queryDebugControlInterfaceStatus != S_OK)
	{
		throw std::exception("Debug control dosn't support");
	}
}

void KdClient::attachKernel(const std::string& parameters)
{
	HRESULT attachKernelResult = pDebugClient->AttachKernel(DEBUG_ATTACH_KERNEL_CONNECTION, parameters.c_str());
	if (attachKernelResult != S_OK)
	{
		std::cout << "Parameters: " << parameters << std::endl;
		std::cout << "Error: 0x" << std::hex << attachKernelResult << std::endl;
		std::cout.unsetf(std::ios::hex);
		throw std::exception("Cann't attach to kernel");
	}
}

void KdClient::waitForEvent()
{
	HRESULT waitForEventResult = pDebugControl->WaitForEvent(DEBUG_WAIT_DEFAULT, INFINITE);
	if (waitForEventResult != S_OK)
	{
		throw std::exception("Target not available");
	}
}

} /* namespace Debugger */
