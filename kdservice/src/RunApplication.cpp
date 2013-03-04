/*
 * RunApplication.cpp
 *
 *  Created on: Feb 28, 2013
 *      Author: Roman Luchyshyn
 */

#include "Command/RunApplication.h"
#include "Server/ServerBuilder.h"

#include "IRunnable.h"
#include "Service.h"

namespace Command {

RunApplication::RunApplication() {
	// TODO Auto-generated constructor stub

}

void RunApplication::start() {
	if (pDebugServer.get() != 0) {
		std::cout << "Run::startAsApp: " << pDebugServer.get() << std::endl;
		throw RunException(ALREADY_RUN, "Critical: Server already exists");
	}

	pDebugServer = Server::ServerBuilder::build(Server::ServerBuilder::DEFAULT_PORT);
	pDebugServer->start();

	IRunnable* pRunnable = dynamic_cast<IRunnable*>(pDebugServer.get());
	if (pRunnable == 0) {
		pDebugServer->stop();
		throw RunException(INTERNAL_ERROR, "Critical: Invalid implementation of server. It is not derived from IRunnable");
	}

	boost::shared_ptr<boost::thread> pThread(new boost::thread(boost::bind(&IRunnable::operator(), pRunnable)));
	pAppThread = pThread;
}

void RunApplication::stop() {
	try {
		Service::LOGGER << log4cpp::Priority::INFO << "Run::startAsApp: <HINT> enter any text to exit";
		std::string exitVar;
		std::cin >> exitVar;
		pDebugServer->stop();
		pAppThread->join();

	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

void RunApplication::join() {
	pAppThread->join();
}

} /* namespace Command */
