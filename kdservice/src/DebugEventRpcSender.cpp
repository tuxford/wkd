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
const unsigned int DebugEventRpcSender::MAX_SENDS_ATTEMPS = 10;
const unsigned int DebugEventRpcSender::TIMEOUT_SEC_ON_UNSUCCESS = 1;

DebugEventRpcSender::DebugEventRpcSender() :
		pXmlrpcClient(0),
		exitThreadFlag(false) {

	pXmlrpcClient = new xmlrpc_c::clientSimple();

	boost::shared_ptr<boost::thread> pThread (new boost::thread(boost::bind(&DebugEventRpcSender::operator(), this)));
	pSendThread = pThread;
}

DebugEventRpcSender::~DebugEventRpcSender() {
	pSendThread->join();
	delete pXmlrpcClient;
}

void DebugEventRpcSender::notify(const Events::ChangeStateEvent& event) {

	try {
		Service::LOGGER << log4cpp::Priority::DEBUG << "DebugEventRpcSender::notifyEvent: (state changed) " << event.getTargetStateInfo().stateId << " message queued";
		messageQueue.push(EventSerializer::servialize(event));
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

void DebugEventRpcSender::operator()() {
//TODO: implement thread join
//TODO: implement message queue for all events (like map<eventType, messageQueue>)
	try {
		Service::LOGGER << log4cpp::Priority::DEBUG << "DebugEventRpcSender::operator (): entry";
		while(true) {
			bool unsuccess = false;
			unsigned int attempsSend = 0;
			while(!messageQueue.empty()) {
				try {
					xmlrpc_c::value result;
					pXmlrpcClient->call(EVENT_LISTENER_URL, STATE_CHANGED_EVENT_METHOD, "s", &result, messageQueue.front().c_str());
					unsuccess = false;
					messageQueue.pop();
					continue;
				}
				catch(std::exception& e) {
					Service::LOGGER << log4cpp::Priority::WARN << "DebugEventRpcSender::operator(): " << e.what();
					unsuccess = true;
					attempsSend++;
				}
				catch(...) {
					Service::LOGGER << log4cpp::Priority::WARN << "DebugEventRpcSender::operator() unknown exception";
					unsuccess = true;
					attempsSend++;
				}

				if (attempsSend > MAX_SENDS_ATTEMPS) {
					unsuccess = false;
					messageQueue.pop();
				}
				else {
					boost::this_thread::sleep(boost::posix_time::seconds(TIMEOUT_SEC_ON_UNSUCCESS));
				}
			}

			if (exitThreadFlag) {
				break;
			}

			boost::thread::yield();
		}
	}
	catch(...) {
		Service::LOGGER << log4cpp::Priority::CRIT << "DebugEventRpcSender::operator() exception in thread! Exited.";
	}
}

} /* namespace Notifier */
