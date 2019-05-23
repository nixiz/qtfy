#ifndef COMPOSITEINTERFACECLASS_H
#define COMPOSITEINTERFACECLASS_H

#include <qtfy.hpp>
#include "icompositeinterface.h"

class CompositeInterfaceClass :
        public Qtfy,
        public IInterface1,
        public IInterface2
{
    Q_OBJECT
public:
    DECLARE_PORT_IN(IInterface1) Interface1Portu;
    DECLARE_PORT_IN(IInterface2) Interface2Portu;

    CompositeInterfaceClass();
    ~CompositeInterfaceClass();
    void Interface1foo();
    void Interface2foo();
private:
    const char* MapEventName(short evID)
    {
        switch (evID) {
        case 21:
            return "Interface1foo";
        case 22:
            return "Interface2foo";
        default:
            return 0;
        }
    }
protected slots:
    void HandleEvent(EventDispatcherHelper* ev);
    void ServiceThreadStarted() {}
    void ServiceThreadFinished() {}
    void ServiceThreadTerminated() {}
    void slotHaberlesmeYoneticisi();
};

#endif // COMPOSITEINTERFACECLASS_H
