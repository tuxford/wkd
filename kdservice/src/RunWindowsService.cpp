/*
 * RunWindowsService.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Roman Luchyshyn
 */

#include "Command/RunWindowsService.h"
#include "Server/ServerBuilder.h"

#include "Service.h"

#include <strsafe.h>

namespace Command {

const unsigned long RunWindowsService::KD_SERVICE_ERROR = 0xE000FFFF;
RunWindowsService* RunWindowsService::pRunWindowsService = 0;

RunWindowsService::RunWindowsService() :
		stopEvent(INVALID_HANDLE_VALUE),
		checkPoint(0),
		serviceStatusHandle(0) {
}

void RunWindowsService::start() {
	if (pRunWindowsService == 0) {
		pRunWindowsService = new RunWindowsService();
		init();
	}

	SERVICE_TABLE_ENTRY serviceTable[] = { {TEXT("Kernel debugger service"), (LPSERVICE_MAIN_FUNCTION)serviceEntry}, {NULL, NULL}};

	if (!StartServiceCtrlDispatcher(serviceTable)) {
		std::wcout << "Run::start StartServiceCtrlDispatcher" << std::endl;
		reportError("StartServiceCtrlDispatcher");
	}

}

void RunWindowsService::stop() {

}

void RunWindowsService::join() {

}

void RunWindowsService::controlHandler(unsigned long controlCode) {
	switch (controlCode) {
		case SERVICE_CONTROL_STOP:
			pRunWindowsService->updateServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
			pRunWindowsService->pDebugServer->stop();
			SetEvent(pRunWindowsService->stopEvent);
			pRunWindowsService->updateServiceStatus(pRunWindowsService->serviceStatus.dwCurrentState, NO_ERROR, 0);
			break;

		case SERVICE_CONTROL_INTERROGATE:
			break;

		default:
			break;
	}
}

bool RunWindowsService::init() {
	stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (stopEvent == NULL) {
		updateServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
		reportError("CreateEvent");
		return false;
	}

//	pDebugServer = Server::ServerBuilder::build(getServerPortFromParameters());
//	boost::shared_ptr<boost::thread> pThread(new boost::thread(*pDebugServer));
//	pServerThread = pThread;

	updateServiceStatus(SERVICE_RUNNING, NO_ERROR, 0);

	while (true) {
		WaitForSingleObject(stopEvent, INFINITE);
		updateServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
		break;
	}

	return true;
}

unsigned int RunWindowsService::getServerPortFromParameters() const {
	unsigned int result = Server::ServerBuilder::DEFAULT_PORT;

	//FIXME: use boost for it

	/*	for (unsigned int i=0; i<parameters.size(); i++)
	 {
	 const std::wstring parameterWithValue = parameters[i];

	 const std::wstring portKeyWithSeparator = L"port:";
	 const unsigned int valuePos = parameterWithValue.find(portKeyWithSeparator);
	 if (valuePos == 0)
	 {
	 const std::wstring valueStr = parameterWithValue.substr(portKeyWithSeparator.size(), parameterWithValue.size() - portKeyWithSeparator.size());
	 std::istringstream iss(valueStr);
	 unsigned int value = 0;
	 iss >> value;
	 result = value;
	 break;
	 }
	 } */

	return result;
}

void RunWindowsService::reportError(const std::string &function) {
	HANDLE eventSource = RegisterEventSource(NULL, Service::NAME.c_str());
	if (eventSource != NULL) {
		const unsigned int maxBufferSize = 200;
		char buffer[maxBufferSize];

		StringCchPrintf(buffer, maxBufferSize, TEXT("%s failed with %d"), function.c_str(), GetLastError());

		char* stringsToSend[] = {const_cast<char*>(Service::NAME.c_str()), buffer};

		ReportEvent(eventSource, EVENTLOG_ERROR_TYPE, 0, KD_SERVICE_ERROR, NULL, 2, 0, (LPCSTR*)stringsToSend, NULL);

		DeregisterEventSource(eventSource);
	}
}

void RunWindowsService::updateServiceStatus(unsigned long currentState, unsigned long exitCode, unsigned long waitHint) {
	serviceStatus.dwCurrentState = currentState;
	serviceStatus.dwWin32ExitCode = exitCode;
	serviceStatus.dwWaitHint = waitHint;

	if (currentState == SERVICE_START_PENDING) {
		serviceStatus.dwControlsAccepted = 0;
	}
	else {
		serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	}

	if ((currentState == SERVICE_RUNNING) || (currentState == SERVICE_STOPPED)) {
		serviceStatus.dwCheckPoint = 0;
	}
	else {
		serviceStatus.dwCheckPoint = checkPoint;
		checkPoint++;
	}

	SetServiceStatus(serviceStatusHandle, &serviceStatus);
}

void RunWindowsService::serviceEntry(int argc, LPSTR*) {
	pRunWindowsService->serviceStatusHandle = RegisterServiceCtrlHandler(Service::NAME.c_str(), (LPHANDLER_FUNCTION)controlHandler);
	if (pRunWindowsService->serviceStatusHandle == 0) {
		reportError("RegisterServiceCtrlHandler");
		return;
	}

	pRunWindowsService->serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	pRunWindowsService->serviceStatus.dwWin32ExitCode = 0;
	const unsigned int waitForStopTimeoutMs = 3000;
	pRunWindowsService->updateServiceStatus(SERVICE_START_PENDING, NO_ERROR, waitForStopTimeoutMs);

	if (!pRunWindowsService->init()) {
		reportError("init()");
	}
}

} /* namespace Command */
