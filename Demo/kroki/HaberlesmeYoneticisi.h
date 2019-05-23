#ifndef HABERLESMEYONETICISI_H
#define HABERLESMEYONETICISI_H

#include <QObject>
#include "ISoyutHaberlesmeYoneticisi.h"
#include "IHaberlesmeYoneticisi.h"
#include <qtfy.hpp>

class HaberlesmeYoneticisi : public Qtfy_T<ISoyutHaberlesmeYoneticisi>, public IHaberlesmeYoneticisi
{
Q_OBJECT
public:
    DECLARE_PORT_IN(IHaberlesmeYoneticisi) HaberlesmeYoneticisiPortu;
    HaberlesmeYoneticisi();
    void bilgiUret(int baglantiNumarasi);
    void Foo(int x);
protected slots:
    void HandleEvent(EventDispatcherHelper* ev);
    void ServiceThreadStarted();
    void ServiceThreadFinished();
    void ServiceThreadTerminated();
};

#endif // HABERLESMEYONETICISI_H
