#include "PeriodiekeIOHandler.h"

PeriodiekeIOHandler::PeriodiekeIOHandler(const uint prio, const uint interval) :
    RTOS::task(prio, "PerIOHandler"),
    m_clock(this, interval, "IO_period")
{}

void PeriodiekeIOHandler::addEventSource(EventSource *ev)
{
    m_evSrcs.push_back(ev);
}

void PeriodiekeIOHandler::main()
{
	std::cout << "PeriodiekeIO suspending" << std::endl;
	suspend();
	std::cout << "PeriodiekeIO a wake" << std::endl;
    while(true)
    {
        wait(m_clock);
		for(EventSource* &es : m_evSrcs)
		{
			es->updateState();
		}
    }
}
