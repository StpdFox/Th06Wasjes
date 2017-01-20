#ifndef __EventSource
#define __EventSource

class EventSource
{
public:
    virtual void updateState(void) = 0;
    virtual ~EventSource(){}
};

#endif
