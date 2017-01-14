#ifndef __Phase
#define __Phase

#include <sys/types.h>

enum Phase
{
	NONE,
    SPOELEN,
    WASSEN,
    CENTRIFUGEREN
};

struct WasProgramPhase
{
	uint number = 0;
    int temp = 0;
    int RPM = 0;
    Phase phase = NONE;
};

#endif
