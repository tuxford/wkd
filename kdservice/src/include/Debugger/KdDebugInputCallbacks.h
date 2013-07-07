/*
 * KdDebugInputCallbacks.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_KdDebugInputCallbacks_H_
#define Debugger_KdDebugInputCallbacks_H_

#include <dbgeng.h>

namespace Debugger {

class KdDebugInputCallbacks: public IDebugInputCallbacks {
public:
	virtual ~KdDebugInputCallbacks();

	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
	virtual HRESULT __stdcall QueryInterface(const REFIID interfaceId, void** pInterface);
	virtual HRESULT __stdcall StartInput(ULONG bufferSize);
	virtual HRESULT __stdcall EndInput();
};

} /* namespace Debugger */

#endif /* Debugger_KdDebugInputCallbacks_H_ */
