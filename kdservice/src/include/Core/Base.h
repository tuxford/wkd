/*
 * Base.h
 *
 *  Created on: Feb 8, 2013
 *      Author: Roman Luchyshyn
 */

#ifndef Core_Base_H_
#define Core_Base_H_


#ifndef SIM
/*#define __in
#define __out
#define __out_bcount
#define __in_bcount
#define __in_bcount_opt
#define __in_opt*/
#include <SpecStrings.h>
#include <dbgeng.h>
#endif

namespace Core
{
#ifdef SIM
	typedef void* DebugClientInterface;
	typedef void* DebugControlInterface;
#else
	typedef ::IDebugClient DebugClientInterface;
	typedef ::IDebugControl DebugControlInterface;
#endif

}

#endif /* Core_Base_H_ */
