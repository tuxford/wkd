/*
 * KdClient.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/KdClient.h"
#include "Debugger/Debugger.h"
#include "Debugger/States/InitialState.h"
#include "Debugger/Events/RanEvent.h"
#include "Service.h"

#include <exception>
#include <iostream>

namespace Debugger {

KdClient::KdClient() :
			pDebugClient(0),
			pDebugControl(0),
			pDebugSymbols(0),
			pTargetStateMachine(0),
			isKernelAttached(false),
			threadFinishFlag(false) {
}

const States::TargetStateInfo KdClient::getTargetStateInfo() const {
	return pTargetStateMachine->context<StateMachine>().getTargetStateInfo();
}

void KdClient::connect() {
	try {
		startMutex.lock();
		threadFinishFlag = false;
		boost::shared_ptr<boost::thread> pThread(new boost::thread(boost::bind(&KdClient::operator(), this)));
		pTargetStateThread = pThread;

		createDebugClient();
		createDebugControl();
		createDebugSymbols();
		setEventHandlers();
	}
	catch (DebugClientException &e) {
		startMutex.unlock();
		if (e.getErrorCode() == UNEXPECTED_ERROR) {
			throw;
		}
	}
}

void KdClient::attachKenel(const std::string& parameters) {
	try {
		attachKernelTarget(parameters);
	}
	catch (DebugClientException &e) {
		if (e.getErrorCode() == UNEXPECTED_ERROR) {
			throw;
		}
	}
}

void KdClient::disconnect() {
	startMutex.unlock();
	threadFinishFlag = true;
	pTargetStateThread->join();

	if (isKernelAttached) {
		pDebugClient->DetachProcesses();
		isKernelAttached = true;
	}

	if (pDebugControl) {
		pDebugControl->Release();
		pDebugControl = 0;
	}
	else {
		//FixMe: memory leak
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Attempt to destroy uninitialized object \"pDebugControl\"");
	}

	if (pDebugClient != 0) {
		pDebugClient->EndSession(DEBUG_END_ACTIVE_DETACH);
		pDebugClient->Release();
		pDebugClient = 0;
	}
	else {
		//FixMe: memory leak
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Attempt to destroy uninitialized object \"pDebugClient\"");
	}
	if (pDebugSymbols) {
		pDebugSymbols->Release();
		pDebugSymbols = 0;
	}

}

void KdClient::setSourcePath(const std::string& sourcePath) {
	if (pDebugSymbols) {
		HRESULT setSourcePathStatus = pDebugSymbols->SetSourcePath(sourcePath.c_str());
		if (setSourcePathStatus != S_OK) {
			BOOST_LOG_TRIVIAL(error) << "Can't set source path. Error: 0x" << std::hex << setSourcePathStatus;
			throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Cann't set source path.");
		}
	}
	else {
		BOOST_LOG_TRIVIAL(warning) << "Attempt to set source path until IDebugSymbols object initialized. Action has no effect.";
	}
}

void KdClient::setSymbolFilePath(const std::string& sourcePath) {
	if (pDebugSymbols) {
		HRESULT setSymbolPathStatus = pDebugSymbols->SetSymbolPath(sourcePath.c_str());
		if (setSymbolPathStatus != S_OK) {
			BOOST_LOG_TRIVIAL(error) << "Can't set symbol path. Error: 0x" << std::hex << setSymbolPathStatus;
			throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Cann't set symbol path.");
		}
	}
	else {
		BOOST_LOG_TRIVIAL(warning) << "Attempt to set symbol path until IDebugSymbols object initialized. Action has no effect.";
	}
}

void KdClient::setDriverReplacemnetMap(const std::string& oldDriver, const std::string& newDriver) {
	if (pDebugControl) {
		const std::string cmd = ".kdfiles -m " + oldDriver + " " + newDriver;
		HRESULT setDriverReplacemnetMapStatus = pDebugControl->Execute(DEBUG_OUTCTL_THIS_CLIENT, cmd.c_str(), DEBUG_EXECUTE_ECHO);
		if (setDriverReplacemnetMapStatus != S_OK) {
			BOOST_LOG_TRIVIAL(warning) << "Can't set driver replacement map. Error: 0x" << std::hex << setDriverReplacemnetMapStatus;
			throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Cann't set driver replacement map.");
		}
	}
	else {
		BOOST_LOG_TRIVIAL(warning) << "Attempt to set driver replacement map until IDebugControl object initialized. Action has no effect.";
	}
}

void KdClient::run() {
	startMutex.unlock();
}

void KdClient::operator ()() {
	try {
		BOOST_LOG_TRIVIAL(debug) << "KdClient::operator(): Thread started";
		startMutex.lock();

		pTargetStateMachine->process_event(Events::RanEvent());

		if (threadFinishFlag == true) {
			return;
		}

		waitForTargetEvent();
	}
	catch(...) {
		BOOST_LOG_TRIVIAL(error) << "KdClient::operator(): exception in the thread";
	}
}

void KdClient::setTargetStateMachine(StateMachine* pStateMachine) {
	this->pTargetStateMachine = pStateMachine;
}

void KdClient::createDebugClient() {

	if (pDebugClient != 0) {
		throw DebugClientException(HandleResult::ALREADY_INITILIZED, "DebugClient already exists.");
	}

	HRESULT debugCreateStatus = ::DebugCreate(__uuidof(IDebugClient), (void**)&pDebugClient);

	if (debugCreateStatus != S_OK ) {
		BOOST_LOG_TRIVIAL(error) << "Cann't initialize debug client. Creation of DebugClient failed. Error: 0x" << std::hex << debugCreateStatus;
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Cann't initialize debug client. Creation of DebugClient failed.");
	}
}

void KdClient::createDebugControl() {

	if (pDebugControl != 0) {
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "DebugControl already exists.");
	}

	HRESULT queryDebugControlInterfaceStatus = pDebugClient->QueryInterface(__uuidof(IDebugControl), (void**)&pDebugControl);

	if (queryDebugControlInterfaceStatus != S_OK ) {
		BOOST_LOG_TRIVIAL(error) << "Debug control dosn't support. Error: 0x" << std::hex << queryDebugControlInterfaceStatus;
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Debug control dosn't support");
	}
}

void KdClient::createDebugSymbols() {
	if (pDebugSymbols != 0) {
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "DebugSymbols already exists.");
	}

	HRESULT queryDebugSymbolsIntefaceStatus = pDebugClient->QueryInterface(__uuidof(IDebugSymbols), (void**)&pDebugSymbols);

	if (queryDebugSymbolsIntefaceStatus != S_OK) {
		BOOST_LOG_TRIVIAL(error) << "Debug symbols dosn't support. Error: 0x" << std::hex << queryDebugSymbolsIntefaceStatus;
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Debug control dosn't support");
	}
}

void KdClient::attachKernelTarget(const std::string& parameters) {
	BOOST_LOG_TRIVIAL(debug) << "KdClient::attachKernel: Parameters: " << parameters;

	if (isKernelAttached == true) {
		throw DebugClientException(HandleResult::ALREADY_ATTACHED_KERNEL, "Kernel already attached");
	}

	HRESULT attachKernelResult = pDebugClient->AttachKernel(DEBUG_ATTACH_KERNEL_CONNECTION, parameters.c_str());
	if (attachKernelResult != S_OK ) {
		BOOST_LOG_TRIVIAL(error) << "KdClient::attachKernel: attach to kernel failed. Parameters: " << parameters;
		BOOST_LOG_TRIVIAL(error) << "Error: 0x" << std::hex << attachKernelResult;
		throw DebugClientException(HandleResult::ATTACH_KERNEL_ERROR, "Cann't attach to kernel.");
	}

	isKernelAttached = true;
}

void KdClient::setEventHandlers() {

	if (pDebugClient != 0) {
		HRESULT setEventCallbacksResult = pDebugClient->SetEventCallbacks(&debugEventCallbacks);
		if (setEventCallbacksResult != S_OK ) {
			BOOST_LOG_TRIVIAL(error) << "KdClient::setEventHandlers: Can't set EventHandlersCallbacks. Error: 0x" << std::hex << setEventCallbacksResult;
			throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Can't set EventHandlersCallbacks");
		}

		/*		HRESULT setInputCallbacksResult = pDebugClient->SetInputCallbacks(&debugInputCallbacks);
		 if (setInputCallbacksResult != S_OK) {
		 BOOST_LOG_TRIVIAL(error) << "KdClient::setEventHandlers: Can't set InputHandlersCallbacks. Error: 0x" << std::hex << setInputCallbacksResult;
		 throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Can't set EventHandlersCallbacks");
		 }*/

		HRESULT setOutputCallbacksResult = pDebugClient->SetOutputCallbacks(pDebugOutputCallbacks.get());
		if (setOutputCallbacksResult != S_OK ) {
			BOOST_LOG_TRIVIAL(error) << "KdClient::setEventHandlers: Can't set OutputHandlersCallbacks. Error: 0x" << std::hex << setOutputCallbacksResult;
			throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Can't set EventHandlersCallbacks");
		}

		BOOST_LOG_TRIVIAL(debug) << "KdClient::setEventHandlers: handlers are installed successfully";
	}
	else {
		BOOST_LOG_TRIVIAL(error) << "KdClient::setEventHandlers: debug client is 0";
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Internal error. Debug client not initialized");
	}
}

void KdClient::waitForTargetEvent() {
	HRESULT setIinitialBreakResult = pDebugControl->SetEngineOptions(DEBUG_ENGOPT_INITIAL_BREAK);
	if (setIinitialBreakResult != S_OK ) {
		BOOST_LOG_TRIVIAL(warning) << "Can't set initial break";
		return;
	}

	while(true) {

		HRESULT waitForEventResult = pDebugControl->WaitForEvent(DEBUG_WAIT_DEFAULT, INFINITE);
		if (waitForEventResult != S_OK ) {
			throw DebugClientException(HandleResult::TARGET_UNAVAILABLE, "Target not available");
		}
	}
}

} /* namespace Debugger */
