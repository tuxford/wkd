/*
 * Run.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Command_Run_H_
#define Command_Run_H_

#include "Server/IDebugServer.h"
#include "Command/IRunService.h"

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace Command {

class Run {
public:
	static bool run(const std::vector<std::wstring> &parameters);
	static void wait();

private:
	static IRunService* pRunService;

	static IRunService* getRunService(const std::vector<std::wstring> &parameters);
};

} /* namespace Command */

#endif /* Command_Run_H_ */
