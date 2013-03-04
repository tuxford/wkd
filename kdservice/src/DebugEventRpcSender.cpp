/*
 * DebugEventRpcSender.cpp
 *
 *  Created on: Feb 13, 2013
 *      Author: Roman Luchyshyn
 */

#include "Notifier/DebugEventRpcSender.h"
#include "Notifier/EventSerializer.h"

#include "Service.h"

namespace Notifier {

const std::string DebugEventRpcSender::EVENT_LISTENER_URL = "http://localhost:21606/xmlrpc";
const std::string DebugEventRpcSender::STATE_CHANGED_EVENT_METHOD = "TargetStateEvent.onEvent";
const std::string DebugEventRpcSender::OUTPUT_EVENT_METHOD = "OutputEvent.onEvent";

DebugEventRpcSender::DebugEventRpcSender() :
		pXmlrpcClient(0) {
	pXmlrpcClient = new xmlrpc_c::clientSimple();
}

DebugEventRpcSender::~DebugEventRpcSender() {
	delete pXmlrpcClient;
}

void DebugEventRpcSender::notify(const Events::ChangeStateEvent& event) {
	xmlrpc_c::value result;

	try {
		Service::LOGGER << log4cpp::Priority::DEBUG << "DebugEventRpcSender::notifyEvent: (state changed) " << EventSerializer::servialize(event);
		pXmlrpcClient->call(EVENT_LISTENER_URL, STATE_CHANGED_EVENT_METHOD, "s", &result, EventSerializer::servialize(event).c_str());
		Service::LOGGER << log4cpp::Priority::DEBUG << "DebugEventRpcSender::notifyEvent: 0";
	}
	catch (std::exception &e) {
//		FIXME: exception
		Service::LOGGER << log4cpp::Priority::WARN << "DebugEventRpcSender::notifyEvent exception: event id> " << event.getTargetStateInfo().stateId;
		Service::LOGGER << log4cpp::Priority::WARN << "DebugEventRpcSender::notifyEvent exception: " << e.what();
	}
	catch (...) {
//		FIXME: exception
		Service::LOGGER << log4cpp::Priority::WARN << "DebugEventRpcSender::notifyEvent unknown exception";
	}
}

void DebugEventRpcSender::notify(const Events::OutputEvent& event) {
	xmlrpc_c::value result;

	try {
		Service::LOGGER << log4cpp::Priority::DEBUG << "DebugEventRpcSender::notifyEvent (debug message): " << event.getMessage();
		pXmlrpcClient->call(EVENT_LISTENER_URL, OUTPUT_EVENT_METHOD, "s", &result, event.getMessage().c_str());
	}
	catch (std::exception &e) {
//		FIXME: exception
		Service::LOGGER << log4cpp::Priority::WARN << "DebugEventRpcSender::notifyEvent exception: " << e.what();
	}
	catch (...) {
//		FIXME: exception
		Service::LOGGER << log4cpp::Priority::WARN << "DebugEventRpcSender::notifyEvent unknown exception";
	}
}

} /* namespace Notifier */