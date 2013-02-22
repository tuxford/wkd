/*
 * KdDebugInputCallbacks.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/KdDebugInputCallbacks.h"

namespace Debugger {

KdDebugInputCallbacks::~KdDebugInputCallbacks() {
}

ULONG KdDebugInputCallbacks::AddRef() {
	return 1;
}

ULONG KdDebugInputCallbacks::Release() {
	return 0;
}

HRESULT KdDebugInputCallbacks::QueryInterface(const REFIID interfaceId, void** ppInterface) {

	*ppInterface = 0;
	if (IsEqualIID(interfaceId, __uuidof(IUnknown)) || IsEqualIID(interfaceId, __uuidof(IDebugInputCallbacks))) {
		*ppInterface = (IDebugInputCallbacks*)this;
		AddRef();
		return S_OK;
	}
	else {
		return E_NOINTERFACE;
	}

}

HRESULT KdDebugInputCallbacks::StartInput(ULONG bufferSize) {

	return S_OK;
}

HRESULT KdDebugInputCallbacks::EndInput() {

	return S_OK;
}

} /* namespace Debugger */
