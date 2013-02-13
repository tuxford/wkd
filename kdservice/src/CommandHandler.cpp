/*
 * CommandHandler.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#include "Command/CommandHandler.h"
#include "Command/Install.h"
#include "Command/Run.h"

#include <iostream>

namespace Command
{

void CommandHandler::handle(const std::vector<std::wstring> &parameters)
{

	if (parameters.size() && (parameters[0] == Install::COMMAND))
	{
		bool isInstallSuccess = false;

		isInstallSuccess = Install::install();

		if (isInstallSuccess)
		{
			std::wcout << "Service has been successfully installed " << std::endl;
		}
		else
		{
			std::wcout << "Service hasn't been installed " << std::endl;
		}
	}
	else
	{
		Run::run(parameters);
	}

}

} /* namespace Command */
