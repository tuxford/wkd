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
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#include <queue>

namespace Notifier {

class DebugEventRpcSender : public IChangeStateNotifier, public IOutputNotifier {
public:
	DebugEventRpcSender();
	~DebugEventRpcSender();

	virtual void notify(const Events::ChangeStateEvent& event);
	virtual void notify(const Events::OutputEvent& event);

	void operator()();
private:
	static const std::string EVENT_LISTENER_URL;
	static const std::string STATE_CHANGED_EVENT_METHOD;
	static const std::string OUTPUT_EVENT_METHOD;
	static const unsigned int MAX_SENDS_ATTEMPS;
	static const unsigned int TIMEOUT_SEC_ON_UNSUCCESS;

	xmlrpc_c::clientSimple* pXmlrpcClient;
	boost::shared_ptr<boost::thread> pSendThread;
	std::queue<std::string> messageQueue;
	bool exitThreadFlag;
};

} /* namespace Notifier */

#endif /* Notifier_Events_DebugEventRpcSender_H_ */
