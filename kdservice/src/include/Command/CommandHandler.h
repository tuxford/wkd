/*
 * CommandHandler.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Command_CommandHandler_H_
#define Command_CommandHandler_H_

#include <string>
#include <vector>

namespace Command {

class CommandHandler {
public:
	static void handle(const std::vector<std::wstring> &parameters);
};

} /* namespace Command */
#endif /* Command_CommandHandler_H_ */
