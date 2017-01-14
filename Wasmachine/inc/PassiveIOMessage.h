#ifndef __PassiveIOMessage
#define __PassiveIOMessage

struct PassiveIOMessage
{
    int doorLock = -1;
    int heater = -1;
    int waterValve = -1;
    int signalLed = -1;
    int pump = -1;
    int motorRPM = 0;
};

#endif