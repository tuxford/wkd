/*
 * KdDebugOutputCallbacks.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: Roman Luchyshyn
 */

#include "Debugger/KdDebugOutputCallbacks.h"

#include "Service.h"

namespace Debugger {

KdDebugOutputCallbacks::KdDebugOutputCallbacks(boost::shared_ptr<Notifier::IOutputNotifier> pNotifier) :
	pOutputNotifier(pNotifier) {
}

KdDebugOutputCallbacks::~KdDebugOutputCallbacks() {

}

ULONG KdDebugOutputCallbacks::AddRef() {
	return 1;
}

ULONG KdDebugOutputCallbacks::Release() {
	return 0;
}

HRESULT KdDebugOutputCallbacks::QueryInterface(const REFIID interfaceId, void** ppInterface) {

	*ppInterface = 0;
	if (IsEqualIID(interfaceId, __uuidof(IUnknown)) || IsEqualIID(interfaceId, __uuidof(IDebugOutputCallbacks))) {
		*ppInterface = (IDebugOutputCallbacks*)this;
		AddRef();
		return S_OK;
	}
	else {
		return E_NOINTERFACE;
	}

}

HRESULT KdDebugOutputCallbacks::Output(ULONG mask, PCSTR text) {
	try {
		Service::LOGGER << log4cpp::Priority::DEBUG << "KdDebugOutputCallbacks::Output: message \"" << text << "\"";
		Notifier::Events::OutputEvent event(text);
		pOutputNotifier->notify(event);
	}
	catch(...) {
		Service::LOGGER << log4cpp::Priority::WARN << "KdDebugOutputCallbacks::Output: message hasn't been sent";
	}
	return S_OK;
}

} /* namespace Debugger */
