#ifndef TIMEOUTSTATE_H
#define TIMEOUTSTATE_H

#include "Rh/RhState.h"

QT_BEGIN_NAMESPACE
class QTimer;
class QState;
QT_END_NAMESPACE

class RhapsodySignalTransition;
class RhTimerState : public RhState
{
Q_OBJECT
public:
    explicit RhTimerState(int mSec,
                          const char *objName,
                          QState *parent = 0);
    // TODO(oguzhank): remove all implementation from code and
    // use new function below!
    RhapsodySignalTransition* setTargetState(QState *targetstate);

    inline RhapsodySignalTransition* setTimeoutState(QState *targetstate)
    {
        return setTargetState(targetstate);
    }

    void onEntry(QEvent *);
    void onExit(QEvent *);
//protected slots:
//    void timerEvent();
signals:
    void TimerExpired();
private:
    QTimer *timer;
};

#endif // TIMEOUTSTATE_H
