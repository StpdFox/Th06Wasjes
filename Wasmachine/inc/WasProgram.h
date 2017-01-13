/*
 * WasProgram.h
 *
 *  Created on: Jan 3, 2017
 *      Author: hendrik
 */

#ifndef INC_WASPROGRAM_H_
#define INC_WASPROGRAM_H_

#include <sys/types.h>

struct WasProgram
{
	uint timeSpoelen = 0;
	uint timeWassing = 0;
	uint temp = 0;
	uint timecentrifugeren = 0;
};


#endif /* INC_WASPROGRAM_H_ */
