/*
 * FakeClient.h
 *
 *  Created on: Feb 17, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_FakeClient_H_
#define Debugger_FakeClient_H_

#include "Debugger/IClient.h"

namespace Debugger {

class FakeClient: public IClient {
public:
	FakeClient();
	virtual ~FakeClient();

	virtual void connect(const std::string& parameters);
	virtual void disconnect();
};

} /* namespace Debugger */
#endif /* Debugger_FakeClient_H_ */
