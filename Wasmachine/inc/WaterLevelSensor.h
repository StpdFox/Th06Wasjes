#ifndef __WaterLevelSensor
#define __WaterLevelSensor

#include "EventSource.h"
#include "WaterLvlListener.h"
#include <sys/types.h>
#include "UartComs.h"

class WaterLevelSensor : public EventSource
{
private:
	UartComs &m_uc;

    const char *m_requestByte;
    uint m_waterLevel = 0;
    WaterLvlListener *m_wlvlListeners;
    
    void readWaterLevel();
    
public:
    WaterLevelSensor(const char *reqByte, UartComs &uc);
    virtual ~WaterLevelSensor();

    void updateState();
    void setListener(WaterLvlListener *wLL);
    uint getWaterLevel() const;
};

#endif
