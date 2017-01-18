/*
 * CurrentState.h
 *
 *  Created on: Jan 18, 2017
 *      Author: hendrik
 */

#ifndef INC_CURRENTSTATUS_H_
#define INC_CURRENTSTATUS_H_

#include <sys/types.h>

#include "Phase.h"

struct CurrentStatus
{
	Phase phase = NONE;
	uint timeRemaining = 0;
};



#endif /* INC_CURRENTSTATUS_H_ */
