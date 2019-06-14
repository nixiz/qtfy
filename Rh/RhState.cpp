/*
 * RhState.cpp
 *  
 * Copyright (C) Oguzhan KATLI
 * All Rights Reserved
 *
 * See the LICENSE file for the terms of usage and distribution.
 *
 */
#include "RhState.h"
#include <QDebug>
#include <QList>
#include <QTimer>

class RhStatePrivate
{
    /*
public:

    RhapsodyEventTransition* addTimer(int mSec, QState *targetstate)
    {
        QTimer *timer = new QTimer(this);
        timer->setInterval(mSec);
        QState::addTransition(timer, SIGNAL(timeout()), targetstate);
        timers.append(timer);
    }

    void addTransition(RhapsodyEventTransition *target)
    {
    }

    void onEntry(QEvent *e)
    {
    }

    void onExit(QEvent *)
    {
    }
private:
    QList<QTimer*> timers;
    */
};

RhState::RhState(const char *objName, QState *parent) :
    QState(parent), pImpl(NULL)
{
    QString name;
    if (parent)
    {
        name.append(parent->objectName());
        name.append(".");
    }
    name.append(objName);
    //qDebug() << "name: " << name;
    setObjectName(name);
    //pImpl = new RhStatePrivate;
}
/*
    QString name;
    QObject *pit = static_cast<QObject *>(parent);
    while(pit)
    {
        name.append(pit->objectName());
        pit = pit->parent();
    }
    qDebug() << "name: " << objName;
    setObjectName(name);
*/

RhState::RhState(const char *objName,
                 ChildMode childMode,
                 QState *parent) :
    QState(childMode, parent), pImpl(NULL), enterEvent(NULL)
{
    QString name;
    if (parent)
    {
        name.append(parent->objectName());
        name.append(".");
    }
    name.append(objName);
    //qDebug() << "name: " << name;
    setObjectName(name);
    //pImpl = new RhStatePrivate;
}

RhState::~RhState()
{
    if (pImpl)
        delete pImpl;
}

void RhState::onEntry(QEvent *e)
{
    //qDebug() << __FUNCTION__ << objectName();
    enterEvent = e;
    QState::onEntry(e);
}

void RhState::onExit(QEvent *e)
{
    //qDebug() << __FUNCTION__ << " " << objectName();
    QState::onExit(e);
}

void RhState::ConnectToOnEnter(QObject* target, const char * slot)
{
    QObject::connect(this, SIGNAL(entered()), target, slot);
}

void RhState::ConnectToOnExit(QObject* target, const char * slot)
{
    QObject::connect(this, SIGNAL(exited()), target, slot);
}

/*
RhapsodyEventTransition* RhState::addTimer(int mSec, QState *targetstate)
{
    QTimer *timer = new QTimer(this);
    timer->setInterval(mSec);
    QState::addTransition(timer, SIGNAL(timeout()), targetstate);
}

void RhState::addTransition(RhapsodyEventTransition *target)
{
    QState::addTransition(target);
}

void RhState::setTargetState(QState *targetstate)
{
    this->addTransition(this, SIGNAL(TimerExpired()), targetstate);
}

void RhState::setGuardForTransition(Guard *guard)
{
    guard_ = guard;
}

void RhState::onEntry(QEvent *e)
{
    qDebug() << __FUNCTION__ << objectName();
    timer->start();
    QState::onEntry(e);
}

void RhState::onExit(QEvent *)
{
    qDebug() << __FUNCTION__ << " " << objectName();
    timer->stop();
}

void RhState::timerEvent()
{
    if (guard_ != 0 && !guard_->Check(objectName())) return;
    emit TimerExpired();
}
*/
