#include "PeriodiekeIOHandler.h"

PeriodiekeIOHandler::PeriodiekeIOHandler(const uint prio, const uint interval) :
    RTOS::task(prio, "PerIOHandler"),
    m_clock(this, interval, "IO_period")
{}

void PeriodiekeIOHandler::addEventSource(const EventSource& *ev)
{
    m_evSrcs.push_back(ev);
}

void PeriodiekeIOHandler::startMonitoring()
{
    set(m_startFlag);
}

void PeriodiekeIOHandler::stopMonitoring()
{
    set(m_stopFlag)
}

void PeriodiekeIOHandler::main()
{
    while(true)
    {
        if(wait() == m_startFlag) m_status = true;
        if(wait() == m_stopFlag) m_status = false;
        
        if(m_status)
        {
            for(EventSource* &es : m_evSrcs)
            {
                es->updateState();
            }
        }
    }
}