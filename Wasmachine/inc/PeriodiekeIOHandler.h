#ifndef __PeriodiekeIOHandler
#define __PeriodiekeIOHandler

#include <vector>

#include "pRTOS.h"
#include "EventSource.h"

class PeriodiekeIOHandler : public RTOS::task
{
private:
    std::vector<EventSource*> m_evSrcs;
    RTOS::clock m_clock;
    
    void main(void);
public:
    PeriodiekeIOHandler(const uint prio, const uint interval);
    void addEventSource(EventSource *ev);
};

#endif
