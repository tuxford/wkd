/*
 * DebugEventCallbacks.h
 *
 *  Created on: Feb 13, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_DebugEventCallbacks_H_
#define Debugger_DebugEventCallbacks_H_

#include "Core/Base.h"

namespace Debugger {

class DebugEventCallbacks: public IDebugEventCallbacks {
public:
	DebugEventCallbacks();
	virtual ~DebugEventCallbacks();

	ULONG AddRef();
	virtual HRESULT Breakpoint(PDEBUG_BREAKPOINT pBreakpoint);
	virtual HRESULT ChangeDebuggeeState(ULONG flags, ULONG64 argument);
	virtual HRESULT ChangeEngineState(ULONG flags, ULONG64 argument);
	virtual HRESULT ChangeSymbolState(ULONG flags, ULONG64 argument);
	virtual HRESULT CreateProcess(ULONG64 imageFileHandle, ULONG64 handle, ULONG64 baseOffset, ULONG moduleSize, PCSTR moduleName, PCSTR imageName, ULONG chekSum, ULONG dateTimeStamp,
			ULONG64 initialThreadHandle, ULONG64 threadDataOffset, ULONG64 startOffset);
	virtual HRESULT CreateThread(ULONG64 handle, ULONG64 dataOffset, ULONG64 startOffset);
	virtual HRESULT Exception(PEXCEPTION_RECORD64 pExceprionRecord, ULONG firstChance);
	virtual HRESULT ExitProcess(ULONG exitCode);
	virtual HRESULT ExitThread(ULONG exitCode);
	virtual HRESULT GetInterestMask(PULONG pMask);
	virtual HRESULT LoadModule(ULONG64 imageFileHandle, ULONG64 baseOffset, ULONG moduleSize, PCSTR moduleName, PCSTR imageName, ULONG checkSum, ULONG dateTimeStamp);
	virtual HRESULT QueryInterface(const REFIID interfaceId, void** pInterface);
	ULONG Release();
	virtual HRESULT SessionStatus(ULONG status);
	virtual HRESULT SystemError(ULONG error, ULONG level);
	virtual HRESULT UnloadModule(PCSTR imageBaseName, ULONG64 baseOffset);

private:
};

} /* namespace Debugger */

#endif /* Debugger_DebugEventCallbacks_H_ */
