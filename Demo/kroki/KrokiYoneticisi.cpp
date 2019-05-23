#include <QDebug>
#include "KrokiYoneticisi.h"
#include "IKrokiBilgiServisi.h"
#include "olaypaketi.h"
#include <QCoreApplication>
#include <oxf/event.h>
#include <oxf/state.h>
#include <QSignalTransition>

#include "icompositeinterface.h"
#include <QThread>

struct Sleeper : public QThread
{
    static void sleep(unsigned long secs)
    {
        QThread::sleep(secs);
    }
};

#define evKBSKrokiGonderId 10

KrokiYoneticisi::KrokiYoneticisi(QObject *parent) : Qtfy(parent)
{
    REGISTER_PORT(KrokiBilgiServisiPortu);
    // root state
    //RhState *calismaTKKBS = new RhState("calismaTKKBS", QState::ParallelStates);
    RH_CREATE_STATE(calismaTKKBS, QState::ParallelStates);
    RH_CREATE_STATE(dinleme, calismaTKKBS);
    RH_CREATE_STATE(bekleme, calismaTKKBS);
    //RhState *bekleme = new RhState("calismaTKKBS.bekleme", calismaTKKBS);

    RH_CREATE_TIMER_STATE(testOneShot, 7000, calismaTKKBS);
    //testOneShot->setObjectName("calismaTKKBS.testOneShot");

    // register in transaction event handler to concrete state
    QSignalTransition * inStateTransaction = new QSignalTransition(this, SIGNAL(signalKYKrokiTalebi(int)));
    QObject::connect(inStateTransaction, SIGNAL(triggered()), this, SLOT(evTransitionHandled()));
    // then add event handler for given transition
    testOneShot->addTransition(inStateTransaction);

    //QState *none = new QState(dinleme);
    RH_CREATE_STATE(none, dinleme);
    QObject::connect(none, SIGNAL(entered()), this, SLOT(HandleStateEnter()));

    RH_CREATE_TIMER_STATE(kekb, 1000, dinleme);
    //RhTimerState *kekb = new RhTimerState(1000, dinleme);
    //kekb->setObjectName("calismaTKKBS.dinleme.kekb");

    RH_CREATE_TIMER_STATE(kbgp, 1000, dinleme);
    //RhTimerState *kbgp = new RhTimerState(1000, dinleme);
    //kbgp->setObjectName("calismaTKKBS.dinleme.kbgp");

    RhapsodyEventTransition *evTr = new RhapsodyEventTransition(evKBSKrokiGonderId, none, kekb);
    /**
     * C++11 ve sonrasý için þu þekilde olabilir:
     * RhapsodyEventTransition *evTr = new RhapsodyEventTransition(evKBSKrokiGonderId, kekb);
     * evTr->addGuard(std::bind(this, &Class::GuardFunc));
     * veya
     * evTr->addGuard([this]() { return this->GuardFunc(); });
     */
    evTr->addGuardFunc(this, &KrokiYoneticisi::TmGuardFunc);
    none->addTransition(evTr);

    kekb->setTargetState(kbgp);
    kbgp->setTargetState(kekb)->addOnTransitionActionFunc(this, &KrokiYoneticisi::OnTransition);

    RH_CREATE_TIMER_STATE(sayma, 10000, bekleme);
    //RhTimerState *sayma = new RhTimerState(10000, bekleme);
    //sayma->setObjectName("calismaTKKBS.sayma");
    sayma->setTargetState(none);

    dinleme->setInitialState(none);
    bekleme->setInitialState(sayma);
    StateChart().addState(calismaTKKBS);
    StateChart().setInitialState(calismaTKKBS);
    setActiveContext(this, true);
}

KrokiYoneticisi::~KrokiYoneticisi()
{

}

bool KrokiYoneticisi::TmGuardFunc(QAbstractTransition const*, QEvent *)
{
    qDebug() << "\n\n" << __FUNCTION__ << "thread: " << QThread::currentThreadId() << "\n";
    return IS_IN(none);
}

bool KrokiYoneticisi::OnTransition(const QAbstractTransition *, QEvent *)
{
    qDebug() << "\n\n" << __FUNCTION__ << "thread: " << QThread::currentThreadId() << "\n";
    return true;
}

void KrokiYoneticisi::evTransitionHandled()
{
    //RhTimerState *enteredState = qobject_cast<RhTimerState*>(sender());
    qDebug() << __FUNCTION__;
}

void KrokiYoneticisi::HandleStateEnter()
{
    QState *enteredState = qobject_cast<QState*>(sender());
    qDebug() << __FUNCTION__ << " => entered state: " << enteredState->objectName();
}

void KrokiYoneticisi::basla()
{
    qDebug(__FUNCTION__);
}

void KrokiYoneticisi::ServiceThreadStarted()
{
    qDebug() << "\n\n" << __FUNCTION__ << "thread: " << QThread::currentThreadId() << "\n";
}

void KrokiYoneticisi::KrokiTalebi()
{
    static int id = 0;
    qDebug(__FUNCTION__);
    //emit evKYKrokiTalebi(id++);
}

void KrokiYoneticisi::MesafeKartiTalebi()
{
    static int id = 0;
    qDebug(__FUNCTION__);

    //OPORT(KrokiBilgiServisiPortu)->GEN(evKYMesafeKartiTalebi(15));
    OPORT(KrokiBilgiServisiPortu)->GEN(evKYMesafeKartiTalebi(15));
}

void KrokiYoneticisi::KBSKrokiGonder(const QString& yeniKroki)
{
    qDebug() << __FUNCTION__ << yeniKroki;
    emit signalKYKrokiTalebi(0);
}

void KrokiYoneticisi::QRAKrokiMesajGonder(int id)
{
    qDebug() << __FUNCTION__ << " id: " << id;
}

void KrokiYoneticisi::HandleEvent(EventDispatcherHelper* ev)
{
    qDebug() << "\n\n" << __FUNCTION__ << "thread: " << QThread::currentThreadId();
    if (IS_EVENT_TYPE_OF(evKBSKrokiGonderId))
    {
        OMSETPARAMS(evKBSKrokiGonder);
        Sleeper::sleep(1);
        KBSKrokiGonder(params->s);

        StateChart().postEvent(ev);
        //if (IS_IN(none))
        //    StateChart().postEvent(ev);
    }
}
