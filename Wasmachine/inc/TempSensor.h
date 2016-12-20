#ifndef __TempSensor
#define __TempSensor

#include "TempListener.h"
#include "EventSource.h"

class TempSensor : public EventSource
{
private:
    char m_reqByte;
    uint m_temp;
    TempListener *m_listener;
    
    void readTemp();
    
public:
    TempSensor(const char reqByte);
    void updateState();
    void setListener(const TempListener *tl);
    uint getTemp() const;
}

#endif