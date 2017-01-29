#ifndef __TempSensor
#define __TempSensor

#include "TempListener.h"
#include "EventSource.h"
#include <sys/types.h>
#include "UartComs.h"

class TempSensor : public EventSource
{
private:
	UartComs &m_uc;

    char m_reqByte;
    uint m_temp = 0;
    TempListener *m_listener;
    
    void readTemp();
    
public:
    TempSensor(const char reqByte, UartComs &uc);
    virtual ~TempSensor();

    void updateState();
    void setListener(TempListener *tl);
    uint getTemp() const;
};

#endif
