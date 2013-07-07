//============================================================================
// Name        : kdservice.cpp
// Author      : Roman Luchyshyn
// Version     :
// Copyright   : (c) Roman Luchyshyn
// Description : Entry point from kernel debugger service
//============================================================================

#include "Command/CommandHandler.h"
#include "Service.h"

#include <iostream>
#ifndef SIM
int wmain(int argc, wchar_t **argv) {
#else
int main(int argc, char **argv) {
#endif
	try {

		std::vector<std::wstring> parameters;
		for (int i = 0; i < argc - 1; i++) {
//			parameters.push_back(std::wstring(argv[i]));
		}

		Command::CommandHandler::handle(parameters);
	}
	catch (std::exception &e) {
		BOOST_LOG_TRIVIAL(fatal) << e.what();
	}
	catch (...) {
		BOOST_LOG_TRIVIAL(fatal) << "Unknown exception";
	}

	return 0;
}

