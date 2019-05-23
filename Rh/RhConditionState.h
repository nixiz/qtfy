#ifndef RHCONDITIONSTATE_H
#define RHCONDITIONSTATE_H

#include <QObject>
#include <QPair>
#include "RhState.h"

class RhapsodySignalTransition;
class RhConditionState : public RhState
{
Q_OBJECT
    struct ConditionFunctorBase
    {
        virtual ~ConditionFunctorBase() {}
        virtual bool CheckCondition(QState *, QEvent *) =0;
    } *conditionCheckFunction;

public:
    typedef QPair<RhapsodySignalTransition*, RhapsodySignalTransition*> IfElseTransitionPair;

    explicit RhConditionState(const char *objName, QState *parent = 0);
    IfElseTransitionPair setConditionState(QState *ifState, QState *elseState);

    template <typename PointerToObj, typename MemFn>
    void SetConditionChecker(const PointerToObj& pObj, const MemFn& pMemFn)
    {
        struct ConditionFunctor : public ConditionFunctorBase
        {
            ConditionFunctor(const PointerToObj& pObj, const MemFn& pMemFn) :
                pObj_(pObj), pMemFn_(pMemFn) { }

            bool CheckCondition(QState *s, QEvent *e) // override
            {
                return ((*pObj_).*pMemFn_)(s, e);
            }
        private:
            PointerToObj pObj_;
            MemFn pMemFn_;
        };
        conditionCheckFunction = new ConditionFunctor(pObj, pMemFn);
    }
    // override connect to enter&exit functions
    void ConnectToOnEnter(QObject* target, const char * slot);
    void ConnectToOnExit(QObject* target, const char * slot);

protected:
    void onEntry(QEvent *ev);
    void onExit(QEvent *);
signals:
    void IfHappened();
    void ElseHappened();
};

#endif // RHCONDITIONSTATE_H
