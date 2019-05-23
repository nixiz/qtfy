#include "CompositeInterfaceClass.h"
#include <QDebug>

CompositeInterfaceClass::CompositeInterfaceClass()
{
    REGISTER_PORT(Interface1Portu);
    REGISTER_PORT(Interface2Portu);
    setActiveContext(this, true);
}

CompositeInterfaceClass::~CompositeInterfaceClass()
{

}
void CompositeInterfaceClass::Interface1foo()
{
    qDebug() << __FUNCTION__;
}

void CompositeInterfaceClass::Interface2foo()
{
    qDebug() << __FUNCTION__;
}

void CompositeInterfaceClass::HandleEvent(EventDispatcherHelper* ev)
{
    StateChart().postEvent(ev);
    delete ev;
}

void CompositeInterfaceClass::slotHaberlesmeYoneticisi()
{
    qDebug() << __FUNCTION__;
}
