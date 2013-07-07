/*
 * KdDebugOutputCallbacks.h
 *
 *  Created on: Feb 21, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_KdDebugOutputCallbacks_H_
#define Debugger_KdDebugOutputCallbacks_H_

#include "Notifier/IOutputNotifier.h"

#include <boost/shared_ptr.hpp>
#include <dbgeng.h>

namespace Debugger {

class KdDebugOutputCallbacks: public IDebugOutputCallbacks {
public:
	KdDebugOutputCallbacks(boost::shared_ptr<Notifier::IOutputNotifier> pOutputNotifier);

	virtual ~KdDebugOutputCallbacks();

	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
	virtual HRESULT __stdcall QueryInterface(const REFIID interfaceId, void** pInterface);
	virtual HRESULT __stdcall Output(ULONG mask, PCSTR text);

public:
	boost::shared_ptr<Notifier::IOutputNotifier> pOutputNotifier;
};

} /* namespace Debugger */

#endif /* Debugger_KdDebugOutputCallbacks_H_ */
