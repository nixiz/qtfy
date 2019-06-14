/*
 * RhTimerState.cpp
 *  
 * Copyright (C) Oguzhan KATLI
 * All Rights Reserved
 *
 * See the LICENSE file for the terms of usage and distribution.
 *
 */
#include "RhTimerState.h"
#include "RhTransitions.hpp"
#include <QObject>
#include <QState>
#include <QTimer>
#include <QDebug>

RhTimerState::RhTimerState(int mSec, const char *objName, QState *parent) :
    RhState(objName, parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SIGNAL(TimerExpired()));
    timer->setInterval(mSec);
}

RhapsodySignalTransition* RhTimerState::setTargetState(QState *targetstate)
{
    if (!targetstate) {
        qWarning("QState::addTransition: cannot add transition to null state");
        return 0;
    }
    // TODO(oguzhank): RhapsodySignalTransition(sourceState : this) yeni ekledimi buraya bak!
    RhapsodySignalTransition *trans = new RhapsodySignalTransition(this, SIGNAL(TimerExpired()), this);
    trans->setTargetState(targetstate);
    addTransition(trans);
    return trans;
}

void RhTimerState::onEntry(QEvent *)
{
    //qDebug() << __FUNCTION__ << objectName();
    timer->start();
}

void RhTimerState::onExit(QEvent *)
{
    //qDebug() << __FUNCTION__ << " " << objectName();
    timer->stop();
}
/*
void RhTimerState::timerEvent()
{
    if (guard_ != 0 && !guard_->Check(objectName())) return;
    emit TimerExpired();
}
*/
