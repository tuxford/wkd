/*
 * TargetStateInfo.h
 *
 *  Created on: Feb 18, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Debugger_States_TargetStateInfo_H_
#define Debugger_States_TargetStateInfo_H_

#include <string>

namespace Debugger {
namespace States {

typedef std::string StateId;

struct TargetStateInfo {
	StateId stateId;
	bool canTerminate;
	bool isTerminated;
	bool canResume;
	bool canSuspend;
	bool isSuspended;
	bool canDisconnect;
	bool isDisconnected;
};

}  // namespace States
}  // namespace Debugger

#endif /* Debugger_States_TargetStateInfo_H_ */
