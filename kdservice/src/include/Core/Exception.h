/*
 * Exception.h
 *
 *  Created on: Feb 15, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Core_Exception_H_
#define Core_Exception_H_

#include <string>

namespace Core {

template <typename T>
class Exception {
public:
	Exception(const T& error, const std::string& messageStr) :
		errorCode(error),
		message(messageStr) {
	}

	std::string getMessage() const {
		return message;
	}

	T getErrorCode() const {
		return errorCode;
	}

private:
	const T errorCode;
	const std::string message;
};

} /* namespace Core */
#endif /* Core_Exception_H_ */
