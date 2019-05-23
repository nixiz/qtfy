#pragma once
#ifndef Qtfy_T_H
#define Qtfy_T_H

#include <QObject>
#include <QThread>
#include <QScopedPointer>
#include <QStateMachine>
#include <QDebug>
#include <QMetaObject>
#include <QEvent>
#include <QStateMachine>
#include <QCoreApplication>
#include "Rh/QRhapsodyInitializer.h"
#include "oxf/event.h"

#define STRINGIFY(s) # s
#define EXPAND_TO_STRING(x) STRINGIFY(x)
#define PORT_RHAPSODY(prt) dynamic_cast< QtfyBase* >(prt)
#define OPORT(prt) PORT_RHAPSODY(prt::out_ptr)
#define OUT_PORT(prt) OPORT(prt::out_ptr)
#define PORT(prt) prt::out_ptr
#define DECLARE_PORT_IN(in) typedef Port_T<in, EmptyType>
#define DECLARE_PORT_OUT(out) typedef Port_T<EmptyType, out>
#define DECLARE_PORT_IN_OUT(in, out) typedef Port_T<in, out>

/** works in gcc compilers only!
 * #define _GET_OVERRIDE(_1, _2, Name, ...) Name
 * #define DECLARE_PORT(...) _GET_OVERRIDE(__VA_ARGS__, DECLARE_PORT_IN_OUT, DECLARE_PORT_IN)(__VA_ARGS__)
*/
#define REGISTER_PORT(Port) PortBinder<Port::InType, Port::OutType>::Register(this)

///
/// \brief The EmptyType class
///
class EmptyType {};
template <class T> class Qtfy_T;

template <class In, class Out>
struct Port_T
{
    typedef In  InType;
    typedef Out OutType;
    static InType  *in_ptr;
    static OutType *out_ptr;
};
template <class In, class Out>
typename Port_T<In,Out>::InType * Port_T<In,Out>::in_ptr = 0;

template <class In, class Out>
typename Port_T<In,Out>::OutType * Port_T<In,Out>::out_ptr = 0;

// DECLARE_PORT_IN_OUT(portIn, portOut) makrosu ile tanýmlanmýþ interfaceler için özelleþtirilmiþtir
// REGISTER_PORT dendiðinde burasý çalýþýr
template <class In, class Out>
struct PortBinder
{
    template <class Servant>
    static void Register(Servant * inptr)
    {
        Port_T<In, Out>::in_ptr = inptr;
        Port_T<Out, In>::out_ptr = inptr;
    }
};

// DECLARE_PORT_IN(port) makrosu ile tanýmlanmýþ interfaceler için özelleþtirilmiþtir
// REGISTER_PORT dendiðinde burasý çalýþýr
template <class In>
struct PortBinder<In, EmptyType>
{
    template <class Servant>
    static void Register(Servant * inptr)
    {
        Port_T<In, EmptyType>::in_ptr = inptr;
        Port_T<EmptyType, In>::out_ptr = inptr;
    }
};

// DECLARE_PORT_OUT(port) makrosu ile tanýmlanmýþ interfaceler için özelleþtirilmiþtir
// REGISTER_PORT dendiðinde burasý çalýþýr
template <class Out>
struct PortBinder<EmptyType, Out>
{
    // Out register'lar için bir þey yapmaya gerek yok zaten ilgili
    // port pair'i in tipindeki sýnýf register ettiðinde oluþacaktýr.
    static void Register(void *) { }
};

struct MetaTypeRegisterHelper
{
    template <class T>
    friend class Qtfy_T;
private:
    MetaTypeRegisterHelper()
    {
        qRegisterMetaType<EventDispatcherHelper*>("EventDispatcherHelper*");
    }
};

struct QtfyBase
{
    virtual bool CallEvent(EventDispatcherHelper* ev) = 0;
};

template <class Obj>
class Qtfy_T : public Obj, public QtfyBase {
public:
    explicit Qtfy_T() { }

    template <class T>
    Qtfy_T(T *parent) : Obj(parent) { }

    virtual ~Qtfy_T() = 0;

    // Use only with GEN() macro!
    bool CallEvent(EventDispatcherHelper* ev)
    {
        // calling thread ile nesnenin yaþadýðý thread ayný ise direk call yapýlabilir
        if (isSameThread(QThread::currentThread()))
        {
            HandleEvent(ev);
            if (ev) delete ev;
        }
        else
        {
            // TODO(oguzhank): async call kullanýldýðýnda return type void olacaðý için
            // burada return deðeri olarak neye göre true veya false dönmeliyiz düþün?!
            QMetaObject::invokeMethod(
                this, "HandleEvent", Qt::QueuedConnection,
                Q_ARG(EventDispatcherHelper*, ev));
        }
        return true;
    }

    inline void setShouldDelete(bool) { }
    inline void initRelations() {}
    inline void initStatechart() {}
    inline void cleanUpRelations() {}
    inline void cancelTimeouts() {}
protected Q_SLOTS:
    Q_INVOKABLE virtual void HandleEvent(EventDispatcherHelper* ev) = 0;
    virtual void ServiceThreadStarted() = 0;
    virtual void ServiceThreadFinished() = 0;
    virtual void ServiceThreadTerminated() = 0;
protected:
    void setActiveContext(Obj *thisobject, bool activeInstance)
    {
        Q_ASSERT_X(!(activeInstance && thisobject != NULL && thisobject != this),
                   __FUNCTION__,
                   "setActiveContext works with own instance!!");
        if(activeInstance) StartServiceThread();
        else // TODO(oguzhank): burayý kontrol et! burada sadece StartStateChart() demek yeterli olabilir.
        {
            if (thisobject && !isSameThread(thisobject->thread()))
            {
                _moveToThread(thisobject->thread());
            }
            else
            {
                // move to main thread
                _moveToThread(QCoreApplication::instance()->thread());
            }
            StartStateChart();
        }
    }

    inline QStateMachine& StateChart() { return statechart; }
    inline void PostEvent(QEvent *event, QStateMachine::EventPriority priority = QStateMachine::NormalPriority)
    {
        statechart.postEvent(event, priority);
    }
    bool isInState(const char * stateName)
    {
        QSetIterator<QAbstractState*> it(StateChart().configuration());
        while (it.hasNext())
        {
            if (it.next()->objectName().contains(stateName, Qt::CaseInsensitive))
                return true;
        }
        return false;
    }
private:
    QStateMachine statechart;
    QScopedPointer<QThread> serviceThread;
    static MetaTypeRegisterHelper _registerMetaTypes;

    inline bool isSameThread(const QThread* otherThread) {
        return this->thread() == otherThread;
    }

    void StartStateChart()
    {
        if (statechart.initialState())
        {
            QObject::connect(QRhapsodyInitializer::instance(), SIGNAL(ConstructionObjectsDone()),
                             &statechart, SLOT(start()),
                             isSameThread(QRhapsodyInitializer::instance()->thread()) ? Qt::DirectConnection : Qt::BlockingQueuedConnection);
        }
    }

    void StartServiceThread() {
        serviceThread.reset(new QThread(this));
        _moveToThread(serviceThread.data());
        statechart.moveToThread(serviceThread.data());
        QObject::connect(serviceThread.data(), SIGNAL(started()), this, SLOT(ServiceThreadStarted()));
        QObject::connect(serviceThread.data(), SIGNAL(finished()), this, SLOT(ServiceThreadFinished()));
#if QT_VERSION >= 0x050000
        // QT5 have not any handle for thread termination.
        //QObject::connect(serviceThread.data(), SIGNAL(destroyed(QObject*)), this, SLOT(ServiceThreadTerminated()));
#else
        QObject::connect(serviceThread.data(), SIGNAL(terminated()), this, SLOT(ServiceThreadTerminated()));
#endif
        StartStateChart();
        serviceThread->start();
    }

    inline void StopServiceThread() {
        // TODO(oguzhank): burasýný kontrol et; doðru sýra bu olmayabilir
        if(!serviceThread.isNull())
        {
            serviceThread->quit();
            serviceThread->wait();
            serviceThread.reset();
        }
    }

    inline void _moveToThread(QThread *thread)
    {
#if QT_VERSION >= 0x050000
        static_cast<QObject*>(this)->moveToThread(thread);
#else
        moveToThread(thread);
#endif
    }
    Q_DISABLE_COPY(Qtfy_T)
};

template <class Obj>
Qtfy_T<Obj>::~Qtfy_T() {
    StopServiceThread();
}

template <>
MetaTypeRegisterHelper Qtfy_T<QObject>::_registerMetaTypes;

typedef Qtfy_T<QObject> Qtfy;

#endif // Qtfy_T_H
