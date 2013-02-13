//============================================================================
// Name        : kdservice.cpp
// Author      : Roman Luchyshyn
// Version     :
// Copyright   : (c) Roman Luchyshyn
// Description : Entry point from kernel debugger service
//============================================================================

#include "Command/CommandHandler.h"

#include <iostream>

int wmain(int argc, wchar_t **argv)
{

	std::vector<std::wstring> parameters;
	for (int i=0; i<argc-1; i++)
	{
		parameters.push_back(std::wstring(argv[i]));
	}

	Command::CommandHandler::handle(parameters);

	return 0;
}

