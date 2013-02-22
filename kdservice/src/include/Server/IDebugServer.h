/*
 * IDebugServer.h
 *
 *  Created on: Feb 12, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Server_IDebugServer_H_
#define Server_IDebugServer_H_


namespace Server
{

class IDebugServer
{
public:
	virtual ~IDebugServer() {}

	virtual void start() = 0;
	virtual void stop() = 0;
};

}

#endif /* Server_IDebugServer_H_ */
