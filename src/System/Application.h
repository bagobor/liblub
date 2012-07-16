/*
 * CommonApplication.h
 *
 *  Created on: Aug 29, 2011
 *      Author: bmonkey
 */

#ifndef COMMONAPPLICATION_H_
#define COMMONAPPLICATION_H_


#ifdef USE_QT_WINDOWS
#include "Window/Qt/QtApplication.h"
typedef QtApplication Application;
#else
#include "Window/XCB/XCBApplication.h"
typedef XCBApplication Application;
#endif


#endif /* COMMONAPPLICATION_H_ */
