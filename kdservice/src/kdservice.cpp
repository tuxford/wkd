//============================================================================
// Name        : kdservice.cpp
// Author      : Roman Luchyshyn
// Version     :
// Copyright   : (c) Roman Luchyshyn
// Description : Entry point from kernel debugger service
//============================================================================

#include "Command/CommandHandler.h"
#include "Service.h"

#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>

#include <iostream>

int wmain(int argc, wchar_t **argv) {

	log4cpp::OstreamAppender *appender = new log4cpp::OstreamAppender("default", &std::cout);
	appender->setLayout(new log4cpp::BasicLayout());
	log4cpp::Category &root = log4cpp::Category::getRoot();
	root.addAppender(appender);
	root.setPriority(log4cpp::Priority::DEBUG);

	root.info("Logger initialized");

	try {

		std::vector<std::wstring> parameters;
		for (int i = 0; i < argc - 1; i++) {
			parameters.push_back(std::wstring(argv[i]));
		}

		Command::CommandHandler::handle(parameters);
	}
	catch (std::exception &e) {
		Service::LOGGER << log4cpp::Priority::FATAL << e.what();
	}
	catch (...) {
		Service::LOGGER << log4cpp::Priority::FATAL << "Unknown exception";
	}

	return 0;
}

