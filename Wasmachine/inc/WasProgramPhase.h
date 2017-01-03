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
    int temp;
    int RPM;
    uint time;
    Phase phase;
};

#endif
