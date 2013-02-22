/*
 * IRunnable.h
 *
 *  Created on: Feb 12, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef IRunnable_H_
#define IRunnable_H_

class IRunnable {
public:
	virtual ~IRunnable() {
	}

	virtual void operator()() = 0;
};

#endif /* IRunnable_H_ */
