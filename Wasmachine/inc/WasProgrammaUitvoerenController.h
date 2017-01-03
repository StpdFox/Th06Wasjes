#include "WasProgramPhase.h"
#include "PassiveIOHandler.h"
//#include "WasProgUitvoerHandler.h"

class WasProgUitvoerHandler;

class WasProgrammaUitvoerenController
{
private:
    PassiveIOHandler &m_pasIOHandler;
    WasProgUitvoerHandler &m_wPUH;
    
    WasProgramPhase m_currentPhase;
    int m_currentTemp = -1;
    uint m_wLevel = 0;
    uint m_targetWLevel = 10;
    bool m_cancelTimer = false;
    bool m_phaseTimer = false;
    bool m_moterLeft = false;
    bool m_heaterOn = false;
    bool m_waterValveOpen = false;
    
    //bool m_perIOHandSuspend = true;

public:
    WasProgrammaUitvoerenController(PassiveIOHandler &pIOHandler, WasProgUitvoerHandler &wPUH);
    void setNewPhase(const WasProgramPhase &wProgPhase);
    void setNewTemp(const uint);
    void setNewWLvl(const uint);
    void cancelTimeOver();
    void phaseTimeOver();
    void checkWasMachine();
};
