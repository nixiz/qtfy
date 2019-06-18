/*
 * qtfy.hpp
 *  
 * Copyright (C) Oguzhan KATLI
 * All Rights Reserved
 *
 * See the LICENSE file for the terms of usage and distribution.
 *
 */
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
#include "ports/include/port.hpp"
#include "Rh/QRhapsodyInitializer.h"
#include "oxf/event.h"

#define STRINGIFY(s) # s
#define EXPAND_TO_STRING(x) STRINGIFY(x)
#define PORT_RHAPSODY(prt) dynamic_cast< QtfyBase* >(prt)
#define OPORT(prt) PORT_RHAPSODY(prt::OutPtr())
#define OUT_PORT(prt) OPORT(prt::OutPtr())
#define setActiveContext(a,b) SetActiveContextRAII activeContextSetter(a,b)

// template <class T> class Qtfy_T;
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
    struct SetActiveContextRAII
    {
        typedef Qtfy_T<Obj> QtfyObj;
        explicit SetActiveContextRAII(QtfyObj *lead, bool activeInstance) : 
            thisObj(lead), mActiveInstance(activeInstance) {}
        ~SetActiveContextRAII()
        {
            thisObj->__setActiveContext(thisObj, mActiveInstance);
        }
    private:
        QtfyObj *thisObj;
        bool mActiveInstance;
    };
    friend struct SetActiveContextRAII;
    explicit Qtfy_T() { }

    template <class T>
    Qtfy_T(T *parent) : Obj(parent) { }

    virtual ~Qtfy_T() = 0;

    // Use only with GEN() macro!
    bool CallEvent(EventDispatcherHelper* ev)
    {
        // calling thread ile nesnenin ya�ad��� thread ayn� ise direk call yap�labilir
        if (isSameThread(QThread::currentThread()))
        {
            HandleEvent(ev);
            if (ev) delete ev;
        }
        else
        {
            // TODO(oguzhank): async call kullan�ld���nda return type void olaca�� i�in
            // burada return de�eri olarak neye g�re true veya false d�nmeliyiz d���n?!
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

    void __setActiveContext(Obj *thisobject, bool activeInstance)
    {
        Q_ASSERT_X(!(activeInstance && thisobject != NULL && thisobject != this),
                   __FUNCTION__,
                   "setActiveContext works with own instance!!");
        if(activeInstance) StartServiceThread();
        else // TODO(oguzhank): buray� kontrol et! burada sadece StartStateChart() demek yeterli olabilir.
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
        // TODO(oguzhank): buras�n� kontrol et; do�ru s�ra bu olmayabilir
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
