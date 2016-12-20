#ifndef __WaterLvlListener
#define __WaterLvlListener

class WaterLevelSensor;

class WaterLvlListener
{
public:
    virtual void updateWLevel(WaterLevelSensor *wls) = 0;
}

#endif