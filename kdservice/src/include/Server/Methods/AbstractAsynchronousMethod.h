/*
 * AbstractAsynchronousMethod.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_AbstractAsynchronousMethod_H_
#define Server_Methods_AbstractAsynchronousMethod_H_

#include "Server/Methods/AbstractMethod.h"
#include "IRunnable.h"

#include <string>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

namespace Server {
namespace Methods {

class AbstractAsynchronousMethod : public AbstractMethod, public IRunnable {
public:
	enum BasicCancelReason {
		NO_CANCEL = 0,
		INVALID_STATE = 1
	};

	AbstractAsynchronousMethod(const std::string& name, const std::string& signature);
	virtual ~AbstractAsynchronousMethod();

	virtual void operator()();

protected:
	virtual unsigned int isActionCanceled() const = 0;
	virtual void handleParameters(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray) = 0;
	virtual void doAction() = 0;
	virtual xmlrpc_value* execute(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray);

private:
	const std::string name;
	const std::string signature;
	boost::mutex executionMutex;
	boost::shared_ptr<boost::thread> pExecutionThread;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_AbstractAsynchronousMethod_H_ */
