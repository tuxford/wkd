/*
 * IRunService.h
 *
 *  Created on: Feb 28, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Command_IRunServide_H_
#define Command_IRunServide_H_

#include "Core/Exception.h"

namespace Command {

enum RunError {
	ALREADY_RUN = 1,
	INTERNAL_ERROR = -1

};
typedef Core::Exception<RunError> RunException;

class IRunService {
public:
	virtual ~IRunService() {}

	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void join() = 0;
};

}  // namespace Command


#endif /* Command_IRunServide_H_ */
