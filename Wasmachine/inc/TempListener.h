#ifndef __TempListener
#define __TempListener

class TempSensor;

class TempListener
{
public:
    virtual void updateTemp(TempSensor *ts) = 0;
    virtual ~TempListener(){}
};

#endif
