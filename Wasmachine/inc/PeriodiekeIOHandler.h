#ifndef __PeriodiekeIOHandler
#define __PeriodiekeIOHandler

#include <vector>

#include "pRTOS.h"
#include "EventSource.h"

class PeriodiekeIOHandler : public RTOS::task
{
private:
    uint m_numberOfEvents;
    bool m_status = false;
    uint m_currentEventSources = 0;
    std::vector<EventSource*> m_evSrcs;
    m_clock = RTOS::clock;
    m_startFlag RTOS::flag;
    m_stopFlag RTOS::flag;
    
    void main();
public:
    PeriodiekeIOHandler(const uint prio, const uint interval);
    void addEventSource(const EventSource& *ev);
    void startMonitoring();
    void stopMonitoring();
};

#endif