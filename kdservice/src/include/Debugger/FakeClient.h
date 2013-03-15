/*
 * FakeClient.h
 *
 *  Created on: Feb 17, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_FakeClient_H_
#define Debugger_FakeClient_H_

#include "Debugger/IClient.h"
#include "Debugger/StateMachine.h"

namespace Debugger {

class FakeClient: public IClient {
public:
	FakeClient();
	virtual ~FakeClient();

	virtual const States::TargetStateInfo getTargetStateInfo() const;
	virtual void connect();
	virtual void attachKenel(const std::string& parameters);
	virtual void disconnect();
	virtual void setSourcePath(const std::string& sourcePath);
	virtual void setSymbolFilePath(const std::string& sourcePath);
	virtual void setDriverReplacemnetMap(const std::string& oldDriver, const std::string& newDriver);
	virtual void run();

	void setTargetStateMachine(StateMachine* pStateMachine);

private:
	StateMachine* pStateMachine;
};

} /* namespace Debugger */
#endif /* Debugger_FakeClient_H_ */
