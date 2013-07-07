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

	ULONG __stdcall AddRef();
	virtual HRESULT __stdcall Breakpoint(PDEBUG_BREAKPOINT pBreakpoint);
	virtual HRESULT __stdcall ChangeDebuggeeState(ULONG flags, ULONG64 argument);
	virtual HRESULT __stdcall ChangeEngineState(ULONG flags, ULONG64 argument);
	virtual HRESULT __stdcall ChangeSymbolState(ULONG flags, ULONG64 argument);
	virtual HRESULT __stdcall CreateProcess(ULONG64 imageFileHandle, ULONG64 handle, ULONG64 baseOffset, ULONG moduleSize, PCSTR moduleName, PCSTR imageName, ULONG chekSum, ULONG dateTimeStamp,
			ULONG64 __stdcall initialThreadHandle, ULONG64 threadDataOffset, ULONG64 startOffset);
	virtual HRESULT __stdcall CreateThread(ULONG64 handle, ULONG64 dataOffset, ULONG64 startOffset);
	virtual HRESULT __stdcall Exception(PEXCEPTION_RECORD64 pExceprionRecord, ULONG firstChance);
	virtual HRESULT __stdcall ExitProcess(ULONG exitCode);
	virtual HRESULT __stdcall ExitThread(ULONG exitCode);
	virtual HRESULT __stdcall GetInterestMask(PULONG pMask);
	virtual HRESULT __stdcall LoadModule(ULONG64 imageFileHandle, ULONG64 baseOffset, ULONG moduleSize, PCSTR moduleName, PCSTR imageName, ULONG checkSum, ULONG dateTimeStamp);
	virtual HRESULT __stdcall QueryInterface(const REFIID interfaceId, void** pInterface);
	ULONG __stdcall Release();
	virtual HRESULT __stdcall SessionStatus(ULONG status);
	virtual HRESULT __stdcall SystemError(ULONG error, ULONG level);
	virtual HRESULT __stdcall UnloadModule(PCSTR imageBaseName, ULONG64 baseOffset);

private:
};

} /* namespace Debugger */

#endif /* Debugger_DebugEventCallbacks_H_ */
