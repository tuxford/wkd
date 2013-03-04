/*
 * KdClient.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_KdClient_H_
#define Debugger_KdClient_H_

#include "Debugger/IClient.h"
#include "Debugger/DebugEventCallbacks.h"
#include "Debugger/KdDebugInputCallbacks.h"
#include "Debugger/KdDebugOutputCallbacks.h"
#include "Core/Exception.h"
#include "Debugger/StateMachine.h"
#include "IRunnable.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

namespace Debugger {

class KdClient: public IClient, public IRunnable {
public:
	KdClient();

	virtual const States::TargetStateInfo getTargetStateInfo() const;
	virtual int connect();
	virtual int attachKenel(const std::string& parameters);
	virtual int disconnect();
	virtual void operator ()();

	void setTargetStateMachine(StateMachine* pStateMachine);
private:
	Core::DebugClientInterface* pDebugClient;
	Core::DebugControlInterface* pDebugControl;
	Core::DebugSymbolsInterface* pDebugSymbols;
	DebugEventCallbacks debugEventCallbacks;
	boost::shared_ptr<KdDebugInputCallbacks> pDebugInputCallbacks;
	boost::shared_ptr<KdDebugOutputCallbacks> pDebugOutputCallbacks;
	StateMachine* pTargetStateMachine;
	bool isKernelAttached;
	boost::mutex startMutex;
	boost::shared_ptr<boost::thread> pTargetStateThread;
	bool threadFinishFlag;

	void createDebugClient();
	void createDebugControl();
	void attachKernelTarget(const std::string& parameters);
	void setEventHandlers();
	void crateDebugSymbols();
	void waitForTargetEvent();
};

} /* namespace Debugger */

#endif /* Debugger_KdClient_H_ */
