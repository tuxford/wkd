/*
 * Run.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#include "Command/Run.h"
#include "Server/ServerBuilder.h"
#include "Service.h"
#include "IRunnable.h"

#include <strsafe.h>
#include <iostream>
#include <boost/thread.hpp>

namespace Command {

const unsigned long Run::KD_SERVICE_ERROR = 0xE000FFFF;
Run* Run::pRun = NULL;

Run::Run(const std::vector<std::wstring> &startParameters) :
			stopEvent(NULL),
			serviceStatusHandle(NULL),
			checkPoint(0),
			parameters(startParameters) {
}

bool Run::run(const std::vector<std::wstring> &parameters) {
	if (pRun != NULL) {
		delete pRun;
	}

	pRun = new Run(parameters);

	try {
//		return pRun->start();
		return pRun->startAsApp();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return false; //For editor!!!
}

void Run::controlHandler(unsigned long controlCode) {
	switch (controlCode) {
		case SERVICE_CONTROL_STOP:
			pRun->updateServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
			pRun->pDebugServer->stop();
			SetEvent(pRun->stopEvent);
			pRun->updateServiceStatus(pRun->serviceStatus.dwCurrentState, NO_ERROR, 0);
			break;

		case SERVICE_CONTROL_INTERROGATE:
			break;

		default:
			break;
	}
}

bool Run::init() {
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

unsigned int Run::getServerPortFromParameters() const {
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

void Run::reportError(const std::string &function) {
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

void Run::updateServiceStatus(unsigned long currentState, unsigned long exitCode, unsigned long waitHint) {
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

void Run::serviceEntry(int argc, LPSTR*) {
	pRun->serviceStatusHandle = RegisterServiceCtrlHandler(Service::NAME.c_str(), (LPHANDLER_FUNCTION)controlHandler);
	if (pRun->serviceStatusHandle == NULL) {
		reportError("RegisterServiceCtrlHandler");
		return;
	}

	pRun->serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	pRun->serviceStatus.dwWin32ExitCode = 0;
	const unsigned int waitForStopTimeoutMs = 3000;
	pRun->updateServiceStatus(SERVICE_START_PENDING, NO_ERROR, waitForStopTimeoutMs);

	if (!pRun->init()) {
		reportError("init()");
	}
}

bool Run::start() {
	SERVICE_TABLE_ENTRY serviceTable[] = { {TEXT("Kernel debugger service"), (LPSERVICE_MAIN_FUNCTION)serviceEntry}, {NULL, NULL}};

	if (!StartServiceCtrlDispatcher(serviceTable)) {
		std::wcout << "Run::start StartServiceCtrlDispatcher" << std::endl;
		reportError("StartServiceCtrlDispatcher");
		return false;
	}

	return true;
}

bool Run::startAsApp() {
	if (pDebugServer.get() != 0) {
		std::cout << "Run::startAsApp: " << pDebugServer.get() << std::endl;
		throw std::exception("Critical: Server already exists");
	}

	pDebugServer = Server::ServerBuilder::build(getServerPortFromParameters());
	pDebugServer->start();

	IRunnable* pRunnable = dynamic_cast<IRunnable*>(pDebugServer.get());
	if (pRunnable == 0) {
		pDebugServer->stop();
		throw std::exception("Critical: Invalid implementation of server. It is not derived from IRunnable");
	}

	boost::thread thread(boost::bind(&IRunnable::operator(), pRunnable));

	try {
		Service::LOGGER << log4cpp::Priority::INFO << "Run::startAsApp: <HINT> enter any text to exit";
		std::string exitVar;
		std::cin >> exitVar;
		pDebugServer->stop();
		thread.join();

	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return true;
}

} /* namespace Command */
