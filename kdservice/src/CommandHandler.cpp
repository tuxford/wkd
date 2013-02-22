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
			Service::LOGGER << log4cpp::Priority::INFO << "Service has been successfully installed ";
		}
		else {
			Service::LOGGER << log4cpp::Priority::FATAL << "Service hasn't been installed ";
		}
	}
	else {
		Run::run(parameters);
	}

}

} /* namespace Command */
