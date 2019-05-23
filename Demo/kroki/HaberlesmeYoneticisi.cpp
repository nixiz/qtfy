#include "HaberlesmeYoneticisi.h"
#include "olaypaketi.h"
#include <QDebug>

HaberlesmeYoneticisi::HaberlesmeYoneticisi()
{
    REGISTER_PORT(HaberlesmeYoneticisiPortu);
    setActiveContext(this, false);
}

void HaberlesmeYoneticisi::bilgiUret(int baglantiNumarasi)
{
    Q_UNUSED(baglantiNumarasi);
}

void HaberlesmeYoneticisi::Foo(int x)
{
    gonder(&x);
}

void HaberlesmeYoneticisi::HandleEvent(EventDispatcherHelper* ev)
{
    qDebug() << "\n\n" << __FUNCTION__ << "thread: " << QThread::currentThreadId();
    if (IS_EVENT_TYPE_OF(10))
    {
        OMSETPARAMS(evKBSKrokiGonder);
        qDebug() << "received message: " << params->s;
    }
}

void HaberlesmeYoneticisi::ServiceThreadStarted()
{

}

void HaberlesmeYoneticisi::ServiceThreadFinished()
{

}

void HaberlesmeYoneticisi::ServiceThreadTerminated()
{

}
