#ifndef __PeriodiekeIOHandler
#define __PeriodiekeIOHandler

#include <vector>

#include "pRTOS.h"
#include "EventSource.h"

class PeriodiekeIOHandler : public RTOS::task
{
private:
    uint m_numberOfEvents;
    bool m_status = true;
    uint m_currentEventSources = 0;
    std::vector<EventSource*> m_evSrcs;
    RTOS::clock m_clock;
    RTOS::flag m_startFlag;
    RTOS::flag m_stopFlag;
    
    void main(void);
public:
    PeriodiekeIOHandler(const uint prio, const uint interval);
    void addEventSource(EventSource *ev);
    void startMonitoring();
    void stopMonitoring();
};

#endif