/*
 * KdAttachKernelMethod.h
 *
 *  Created on: Feb 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_Methods_KdAttachKernelMethod_H_
#define Server_Methods_KdAttachKernelMethod_H_

#include "Server/Methods/AbstractAsynchronousMethod.h"
#include "Debugger/StateMachine.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

namespace Server {
namespace Methods {

class KdAttachKernelMethod: public AbstractAsynchronousMethod {

public:
	KdAttachKernelMethod(boost::shared_ptr<Debugger::StateMachine> pStateMachine);
//	virtual ~KdAttachKernelMethod();

protected:
	virtual unsigned int isActionCanceled() const;
	virtual void handleParameters(xmlrpc_env* const pEnv, xmlrpc_value * const pParamArray);
	virtual void doAction();

private:
	static const std::string METHOD_NAME;
	static const std::string METHOD_SIGNATURE;


	boost::shared_ptr<Debugger::StateMachine> pStateMachine;
	std::string connectParameters;
};

} /* namespace Methods */
} /* namespace Server */

#endif /* Server_Methods_KdAttachKernelMethod_H_ */
