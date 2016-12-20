#ifndef __WaterLevelSensor
#define __WaterLevelSensor

#include "EventSource.h"
#include "WaterLvlListener.h"
#include <sys/types.h>

class WaterLevelSensor : public EventSource
{
private:
    char m_requestByte;
    uint m_waterLevel;
    WaterLvlListener *m_wlvlListeners;
    
    void readWaterLevel();
    
public:
    WaterLevelSensor(const char reqByte);
    void updateState();
    void setListener(WaterLvlListener *wLL);
    uint getWaterLevel() const;
};

#endif