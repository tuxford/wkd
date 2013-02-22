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

	virtual ULONG AddRef();
	virtual ULONG Release();
	virtual HRESULT QueryInterface(const REFIID interfaceId, void** pInterface);
	virtual HRESULT StartInput(ULONG bufferSize);
	virtual HRESULT EndInput();
};

} /* namespace Debugger */

#endif /* Debugger_KdDebugInputCallbacks_H_ */
