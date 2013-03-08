/*
 * KdClient.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/KdClient.h"
#include "Debugger/Debugger.h"
#include "Debugger/States/InitialState.h"
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
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Attempt to destroy uninitialized object \"pDebugControl\"");
	}

	if (pDebugClient != 0) {
		pDebugClient->EndSession(DEBUG_END_ACTIVE_DETACH);
		pDebugClient->Release();
		pDebugClient = 0;
	}
	else {
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Attempt to destroy uninitialized object \"pDebugClient\"");
	}
}

void KdClient::operator ()() {
	Service::LOGGER << log4cpp::Priority::DEBUG << "KdClient::operator(): Thread started";
	startMutex.lock();
	if (threadFinishFlag == true) {
		return;
	}
	waitForTargetEvent();
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
		Service::LOGGER << log4cpp::Priority::CRIT << "Cann't initialize debug client. Creation of DebugClient failed. Error: 0x" << std::hex << debugCreateStatus;
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Cann't initialize debug client. Creation of DebugClient failed.");
	}
}

void KdClient::createDebugControl() {

	if (pDebugControl != 0) {
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "DebugControl already exists.");
	}

	HRESULT queryDebugControlInterfaceStatus = pDebugClient->QueryInterface(__uuidof(IDebugControl), (void**)&pDebugControl);

	if (queryDebugControlInterfaceStatus != S_OK ) {
		Service::LOGGER << log4cpp::Priority::CRIT << "Debug control dosn't support. Error: 0x" << std::hex << queryDebugControlInterfaceStatus;
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Debug control dosn't support");
	}
}

void KdClient::attachKernelTarget(const std::string& parameters) {
	Service::LOGGER << log4cpp::Priority::DEBUG << "KdClient::attachKernel: Parameters: " << parameters;

	if (isKernelAttached == true) {
		throw DebugClientException(HandleResult::ALREADY_ATTACHED_KERNEL, "Kernel already attached");
	}

	HRESULT attachKernelResult = pDebugClient->AttachKernel(DEBUG_ATTACH_KERNEL_CONNECTION, parameters.c_str());
	if (attachKernelResult != S_OK ) {
		Service::LOGGER << log4cpp::Priority::
		ERROR << "KdClient::attachKernel: attach to kernel failed. Parameters: " << parameters;
		Service::LOGGER << log4cpp::Priority::
		ERROR << "Error: 0x" << std::hex << attachKernelResult;
		throw DebugClientException(HandleResult::ATTACH_KERNEL_ERROR, "Cann't attach to kernel.");
	}

	isKernelAttached = true;
}

void KdClient::setEventHandlers() {

	if (pDebugClient != 0) {

		HRESULT setEventCallbacksResult = pDebugClient->SetEventCallbacks(&debugEventCallbacks);
		if (setEventCallbacksResult != S_OK ) {
			Service::LOGGER << log4cpp::Priority::CRIT << "KdClient::setEventHandlers: Can't set EventHandlersCallbacks. Error: 0x" << std::hex << setEventCallbacksResult;
			throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Can't set EventHandlersCallbacks");
		}

		/*		HRESULT setInputCallbacksResult = pDebugClient->SetInputCallbacks(&debugInputCallbacks);
		 if (setInputCallbacksResult != S_OK) {
		 Service::LOGGER << log4cpp::Priority::CRIT << "KdClient::setEventHandlers: Can't set InputHandlersCallbacks. Error: 0x" << std::hex << setInputCallbacksResult;
		 throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Can't set EventHandlersCallbacks");
		 }*/

		HRESULT setOutputCallbacksResult = pDebugClient->SetOutputCallbacks(pDebugOutputCallbacks.get());
		if (setOutputCallbacksResult != S_OK ) {
			Service::LOGGER << log4cpp::Priority::CRIT << "KdClient::setEventHandlers: Can't set OutputHandlersCallbacks. Error: 0x" << std::hex << setOutputCallbacksResult;
			throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Can't set EventHandlersCallbacks");
		}

		Service::LOGGER << log4cpp::Priority::DEBUG << "KdClient::setEventHandlers: handlers are installed successfully";
	}
	else {
		Service::LOGGER << log4cpp::Priority::CRIT << "KdClient::setEventHandlers: debug client is 0";
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Internal error. Debug client not initialized");
	}
}

void KdClient::waitForTargetEvent() {
	HRESULT setIinitialBreakResult = pDebugControl->SetEngineOptions(DEBUG_ENGOPT_INITIAL_BREAK);
	if (setIinitialBreakResult != S_OK ) {
		throw DebugClientException(HandleResult::UNEXPECTED_ERROR, "Can't set initial break");
	}

	HRESULT waitForEventResult = pDebugControl->WaitForEvent(DEBUG_WAIT_DEFAULT, INFINITE);
	if (waitForEventResult != S_OK ) {
		throw DebugClientException(HandleResult::TARGET_UNAVAILABLE, "Target not available");
	}
}

} /* namespace Debugger */
