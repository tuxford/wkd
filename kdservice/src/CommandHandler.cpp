/*
 * CommandHandler.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#include "Command/CommandHandler.h"
#include "Command/Install.h"
#include "Command/Run.h"
#include "Service.h"

#include <iostream>

namespace Command {

void CommandHandler::handle(const std::vector<std::wstring> &parameters) {
	if (parameters.size() && (parameters[0] == Install::COMMAND)) {
		bool isInstallSuccess = false;

		isInstallSuccess = Install::install();

		if (isInstallSuccess) {
			BOOST_LOG_TRIVIAL(info) << "Service has been successfully installed ";
		}
		else {
			BOOST_LOG_TRIVIAL(fatal) << "Service hasn't been installed ";
		}
	}
	else {
		Run::run(parameters);
		Run::wait();
	}

}

} /* namespace Command */
