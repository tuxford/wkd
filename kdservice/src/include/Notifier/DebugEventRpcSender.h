/*
 * DebugEventRpcSender.h
 *
 *  Created on: Feb 13, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Notifier_Events_DebugEventRpcSender_H_
#define Notifier_Events_DebugEventRpcSender_H_

#include "Notifier/Events/ChangeStateEvent.h"
#include "Notifier/Events/OutputEvent.h"
#include "Notifier/IChangeStateNotifier.h"
#include "Notifier/IOutputNotifier.h"

#include <xmlrpc-c/client_simple.hpp>

namespace Notifier {

class DebugEventRpcSender : public IChangeStateNotifier, public IOutputNotifier {
public:
	DebugEventRpcSender();
	~DebugEventRpcSender();

	virtual void notify(const Events::ChangeStateEvent& event);
	virtual void notify(const Events::OutputEvent& event);

private:
	static const std::string EVENT_LISTENER_URL;
	static const std::string STATE_CHANGED_EVENT_METHOD;
	static const std::string OUTPUT_EVENT_METHOD;

	xmlrpc_c::clientSimple* pXmlrpcClient;
};

} /* namespace Notifier */

#endif /* Notifier_Events_DebugEventRpcSender_H_ */
