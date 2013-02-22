/*
 * Service.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Service_H_
#define Service_H_

#include <log4cpp/Category.hh>
#include <string>

namespace Service
{
	static const std::string NAME = "kdservice";
	static log4cpp::Category& LOGGER = log4cpp::Category::getRoot();
};


#endif /* SERVICE_H_ */
