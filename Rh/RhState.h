#ifndef RHSTATE_H
#define RHSTATE_H

#include <QState>

class RhStatePrivate;
class RhapsodyEventTransition;

class RhState : public QState
{
Q_OBJECT
public:
    RhState(const char *objName, QState *parent = 0);
    RhState(const char *objName, ChildMode childMode, QState *parent = 0);
    ~RhState();

    void ConnectToOnEnter(QObject* target, const char * slot);
    void ConnectToOnExit(QObject* target, const char * slot);
    //RhapsodyEventTransition* addTimer(int mSec, QState *targetstate = 0);
    //void addTransition(RhapsodyEventTransition *target);
protected:
    void onEntry(QEvent *e);
    void onExit(QEvent *e);
    inline QEvent *getEvent() const
    {
        return enterEvent;
    }
private:
    RhStatePrivate *pImpl;
    QEvent *enterEvent;
};

#endif // RHSTATE_H
