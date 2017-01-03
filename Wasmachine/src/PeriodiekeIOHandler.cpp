#include "PeriodiekeIOHandler.h"

PeriodiekeIOHandler::PeriodiekeIOHandler(const uint prio, const uint interval) :
    RTOS::task(prio, "PerIOHandler"),
	m_numberOfEvents(0),
    m_clock(this, interval, "IO_period"),
    m_startFlag(this, "StartFlag"),
    m_stopFlag(this, "StopFlag")
{}

void PeriodiekeIOHandler::addEventSource(EventSource *ev)
{
    m_evSrcs.push_back(ev);
}

void PeriodiekeIOHandler::startMonitoring()
{
    set(m_startFlag);
}

void PeriodiekeIOHandler::stopMonitoring()
{
    set(m_stopFlag);
}

void PeriodiekeIOHandler::main()
{
	suspend();
    while(true)
    {
        wait(m_clock);
		for(EventSource* &es : m_evSrcs)
		{
			es->updateState();
		}
    }
}
