/*
 * RunApplication.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Command_RunApplication_H_
#define Command_RunApplication_H_

#include "Command/IRunService.h"
#include "Server/IDebugServer.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

namespace Command {

class RunApplication : public IRunService{
public:
	RunApplication();

	virtual void start();
	virtual void stop();
	virtual void join();

private:
	boost::shared_ptr<Server::IDebugServer> pDebugServer;
	boost::shared_ptr<boost::thread> pAppThread;

	bool startAsApp();
};

} /* namespace Command */
#endif /* Command_RunApplication_H_ */
