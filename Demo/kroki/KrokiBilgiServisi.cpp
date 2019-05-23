#include "KrokiBilgiServisi.h"
#include "IKrokiYoneticisi.h"
#include "olaypaketi.h"
#include "icompositeinterface.h"
#include "ISoyutHaberlesmeYoneticisi.h"
#include <QDebug>
#include <oxf/event.h>

KrokiBilgiServisi::KrokiBilgiServisi(QObject *parent) : Qtfy(parent)
{
    REGISTER_PORT(KrokiBilgiServisiPortu);
    REGISTER_PORT(InterfaceIPortu);
    REGISTER_PORT(HaberlesmeYoneticisiPortu);
    //setVeriErisimci(new KrokiBilgiServisiVeriErisimci);
    setActiveContext(this, true);
}

KrokiBilgiServisi::~KrokiBilgiServisi()
{

}

void KrokiBilgiServisi::basla()
{
    qDebug(__FUNCTION__);
}

bool KrokiBilgiServisi::durumHaritalariniSil()
{
    qDebug(__FUNCTION__);
    return false;
}

void KrokiBilgiServisi::krokileriSil()
{
    qDebug(__FUNCTION__);
    //res = false;
}

void KrokiBilgiServisi::KYKrokiTalebi(int id)
{
    Q_UNUSED(id);
    qDebug() << __FUNCTION__ << "(" << id << ")";

    PORT(InterfaceIPortu)->Interface1foo();
    PORT(HaberlesmeYoneticisiPortu)->Foo(11);
    OPORT(HaberlesmeYoneticisiPortu)->GEN(evKBSKrokiGonder("GenCall::ISoyutHaberlesmeYoneticisi"));
    //dynamic_cast< Qtfy_T<ISoyutHaberlesmeYoneticisi>* >(HaberlesmeYoneticisiPortu::out_ptr)->GEN(evKBSKrokiGonder("GenCall::ISoyutHaberlesmeYoneticisi"));

    OPORT(KrokiBilgiServisiPortu)->GEN(evKBSKrokiGonder("GenCall"));
}

void KrokiBilgiServisi::KYMesafeKartiTalebi(int id)
{
    qDebug() << __FUNCTION__ << "(" << id << ")";
    Q_UNUSED(id);
}

void KrokiBilgiServisi::QRAGUIBrifingAc(QString ad)
{
    qDebug(__FUNCTION__);
    Q_UNUSED(ad);
}

void KrokiBilgiServisi::QRAGUIKrokiTalebi(int id)
{
    Q_UNUSED(id);
    qDebug(__FUNCTION__);
}
/*
void KrokiBilgiServisi::ServiceThreadStarted() {
    qDebug() << "\n\n" << __FUNCTION__ << "thread: " << QThread::currentThreadId();
}

void KrokiBilgiServisi::ServiceThreadFinished() {
    qDebug(__FUNCTION__);
}

void KrokiBilgiServisi::ServiceThreadTerminated() {
    qDebug(__FUNCTION__);
}
*/
void KrokiBilgiServisi::HandleEvent(EventDispatcherHelper* ev)
{
    qDebug() << "\n\n" << __FUNCTION__ << "thread: " << QThread::currentThreadId() << "\n";
    if (IS_EVENT_TYPE_OF(11))
    {
        OMSETPARAMS(evKYMesafeKartiTalebi);
        KYMesafeKartiTalebi(params->_i);
    }
    delete ev;
}
