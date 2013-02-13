/*
 * CommandHandler.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Command_Install_H_
#define Command_Install_H_

#include <string>

namespace Command {

class Install {
public:
	static const std::wstring COMMAND;

	static bool install();

private:
};

} /* namespace Command */

#endif /* Command_Install_H_ */
