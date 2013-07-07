/*
 * AbstractAsynchronousMethod.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#include "Server/Methods/AbstractAsynchronousMethod.h"
#include "Debugger/Debugger.h"
#include "Service.h"

#include <boost/interprocess/sync/scoped_lock.hpp>

#include <iostream>

namespace Server {
namespace Methods {

AbstractAsynchronousMethod::AbstractAsynchronousMethod(const std::string& methodName, const std::string& methodSignature) :
		AbstractMethod(methodName, methodSignature) {
}

AbstractAsynchronousMethod::~AbstractAsynchronousMethod() {
	BOOST_LOG_TRIVIAL(warning) << "AbstractAsynchronousMethod::~AbstractAsynchronousMethod: ";
	if (pExecutionThread.get()) {
		pExecutionThread->join();
	}
}

xmlrpc_value* AbstractAsynchronousMethod::execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) {
	try {
		unsigned int cancelReason = isActionCanceled();
		if (cancelReason) {
			return xmlrpc_build_value(pEnv, "i", cancelReason);
		}

		if (pExecutionThread.get()) {
			BOOST_LOG_TRIVIAL(warning) << "AbstractAsynchronousMethod::execute: thread is initialized. ";
		}

		boost::interprocess::scoped_lock<boost::mutex> lock(executionMutex);

		handleParameters(pEnv, pParamArray);

		boost::shared_ptr<boost::thread> pThread(new boost::thread(boost::bind(&IRunnable::operator(), this)));
		pExecutionThread = pThread;

		BOOST_LOG_TRIVIAL(debug) << "AbstractAsynchronousMethod::execute: scheduled successfully";
		return xmlrpc_build_value(pEnv, "i", 0);

	}
	catch (Debugger::DebugClientException &e) {
		BOOST_LOG_TRIVIAL(error) << "AbstractAsynchronousMethod::execute: connect exception: " << e.getMessage();
		return xmlrpc_build_value(pEnv, "i", (e.getErrorCode() < 0) ? e.getErrorCode() : -e.getErrorCode());
	}
	catch (...) {
		BOOST_LOG_TRIVIAL(error) << "AbstractAsynchronousMethod::execute: unknown exception";
		return xmlrpc_build_value(pEnv, "i", Debugger::INTERNAL_ERROR);
	}

	return 0;
}

void AbstractAsynchronousMethod::operator()() {
	try {
		boost::interprocess::scoped_lock<boost::mutex> lock(executionMutex);
		doAction();
	}
	catch(...) {
		BOOST_LOG_TRIVIAL(error) << "AbstractAsynchronousMethod::operator(): unknown exception in thread method";
	}
}

} /* namespace Methods */
} /* namespace Server */
