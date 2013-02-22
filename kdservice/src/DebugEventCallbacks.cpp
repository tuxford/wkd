/*
 * EventCallbacks.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/DebugEventCallbacks.h"

namespace Debugger {

DebugEventCallbacks::DebugEventCallbacks() {
}

DebugEventCallbacks::~DebugEventCallbacks() {
}

ULONG DebugEventCallbacks::AddRef() {
	return 1;
}

HRESULT DebugEventCallbacks::Breakpoint(PDEBUG_BREAKPOINT pBreakpoint) {
	return DEBUG_STATUS_BREAK;
}

HRESULT DebugEventCallbacks::ChangeDebuggeeState(ULONG flags, ULONG64 argument) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::ChangeEngineState(ULONG flags, ULONG64 argument) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::ChangeSymbolState(ULONG flags, ULONG64 argument) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::CreateProcess(ULONG64 imageFileHandle, ULONG64 handle, ULONG64 baseOffset, ULONG moduleSize, PCSTR moduleName, PCSTR imageName, ULONG chekSum, ULONG dateTimeStamp,
		ULONG64 initialThreadHandle, ULONG64 threadDataOffset, ULONG64 startOffset) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::CreateThread(ULONG64 handle, ULONG64 dataOffset, ULONG64 startOffset) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::Exception(PEXCEPTION_RECORD64 pExceprionRecord, ULONG firstChance) {
	return DEBUG_STATUS_BREAK;
}

HRESULT DebugEventCallbacks::ExitProcess(ULONG exitCode) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::ExitThread(ULONG exitCode) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::GetInterestMask(PULONG pMask) {
	*pMask = DEBUG_EVENT_BREAKPOINT | DEBUG_EVENT_EXCEPTION | DEBUG_EVENT_CREATE_THREAD | DEBUG_EVENT_EXIT_THREAD | DEBUG_EVENT_CREATE_PROCESS | DEBUG_EVENT_EXIT_PROCESS | DEBUG_EVENT_LOAD_MODULE
			| DEBUG_EVENT_UNLOAD_MODULE | DEBUG_EVENT_SYSTEM_ERROR | DEBUG_EVENT_SESSION_STATUS | DEBUG_EVENT_CHANGE_DEBUGGEE_STATE | DEBUG_EVENT_CHANGE_ENGINE_STATE | DEBUG_EVENT_CHANGE_SYMBOL_STATE;

	return S_OK ;
}

HRESULT DebugEventCallbacks::LoadModule(ULONG64 imageFileHandle, ULONG64 baseOffset, ULONG moduleSize, PCSTR moduleName, PCSTR imageName, ULONG checkSum, ULONG dateTimeStamp) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::QueryInterface(const REFIID interfaceId, void** pInterface)
{
	*pInterface = 0;
	if (IsEqualIID(interfaceId, __uuidof(IUnknown)) || IsEqualIID(interfaceId, __uuidof(IDebugEventCallbacks)))
	{
		*pInterface = this;
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

ULONG DebugEventCallbacks::Release() {
	return 0;
}

HRESULT DebugEventCallbacks::SessionStatus(ULONG status) {
	return DEBUG_STATUS_NO_CHANGE;
}

HRESULT DebugEventCallbacks::SystemError(ULONG error, ULONG level) {
	return DEBUG_STATUS_BREAK;
}

HRESULT DebugEventCallbacks::UnloadModule(PCSTR imageBaseName, ULONG64 baseOffset) {
	return DEBUG_STATUS_NO_CHANGE;
}

} /* namespace Server */
