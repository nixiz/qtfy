#include "RhConditionState.h"
#include "RhTransitions.hpp"
//#include "qtfy.hpp"
#include <QDebug>

RhConditionState::RhConditionState(const char *objName,
                                   QState *parent) :
    RhState(objName, parent), conditionCheckFunction(NULL) { }

RhConditionState::IfElseTransitionPair RhConditionState::setConditionState(QState *ifState, QState *elseState)
{
    RhapsodySignalTransition *ifTrans = new RhapsodySignalTransition(this, SIGNAL(IfHappened()), this);
    ifTrans->setTargetState(ifState);
    addTransition(ifTrans);

    RhapsodySignalTransition *elseTrans = new RhapsodySignalTransition(this, SIGNAL(IfHappened()), this);
    elseTrans->setTargetState(elseState);
    addTransition(elseTrans);

    return IfElseTransitionPair(ifTrans, elseTrans);
}

void RhConditionState::onEntry(QEvent *ev)
{
    //qDebug() << __FUNCTION__ << "\n";
    Q_ASSERT(conditionCheckFunction != NULL);
    if (conditionCheckFunction && conditionCheckFunction->CheckCondition(this, ev))
        emit IfHappened();
    else
        emit ElseHappened();
}

void RhConditionState::onExit(QEvent *)
{
    //qDebug() << __FUNCTION__ << "\n";
}

void RhConditionState::ConnectToOnEnter(QObject*, const char *)
{
    Q_ASSERT_X(false, __FUNCTION__, "Cannot add connection Enter or Exit state for Condition State");
}

void RhConditionState::ConnectToOnExit(QObject*, const char *)
{
    Q_ASSERT_X(false, __FUNCTION__, "Cannot add connection Enter or Exit state for Condition State");
}
