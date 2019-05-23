#ifndef RHTRANSITIONS_HPP
#define RHTRANSITIONS_HPP

#include <QAbstractTransition>
#include <QSignalTransition>
#include "oxf/event.h"

template <class QTransition> // where QTransition must be derived form QAbstractTransition
class RhTransitionOverrides : public QTransition
{
    struct FunctionCallerBase
    {
        virtual ~FunctionCallerBase() {}
        virtual bool CallFunc(QAbstractTransition const*, QEvent *) =0;
    } *guardFunctorPtr, *onTransitionActionPtr;

    template <typename PointerToObj, typename MemFn>
    struct FunctionCaller : public FunctionCallerBase
    {
        FunctionCaller(const PointerToObj& pObj, const MemFn& pMemFn) :
            pObj_(pObj), pMemFn_(pMemFn) { }

        bool CallFunc(QAbstractTransition const* t, QEvent *e) // override
        {
            return ((*pObj_).*pMemFn_)(t, e);
        }
    private:
        PointerToObj pObj_;
        MemFn pMemFn_;
    };
public:
    explicit RhTransitionOverrides(QState *sourceState = 0) :
        QTransition(sourceState),
        guardFunctorPtr(NULL),
        onTransitionActionPtr(NULL) { }

    // support secondary ctor for Qt Transition objects
    template <typename Arg1, typename Arg2>
    RhTransitionOverrides(Arg1 arg1, Arg2 arg2, QState *sourceState = 0) :
        QTransition(arg1, arg2, sourceState),
        guardFunctorPtr(NULL),
        onTransitionActionPtr(NULL) { }

    // TODO(oguzhank): make dtor virtual if should be
    ~RhTransitionOverrides()
    {
        if (guardFunctorPtr)
            delete guardFunctorPtr;
        if (onTransitionActionPtr)
            delete onTransitionActionPtr;
    }

    template <typename PointerToObj, typename MemFn>
    inline void addGuardFunc(const PointerToObj& pObj, const MemFn& pMemFn)
    {
        guardFunctorPtr = new FunctionCaller<PointerToObj, MemFn>(pObj, pMemFn);
    }

    template <typename PointerToObj, typename MemFn>
    inline void addOnTransitionActionFunc(const PointerToObj& pObj, const MemFn& pMemFn)
    {
        onTransitionActionPtr = new FunctionCaller<PointerToObj, MemFn>(pObj, pMemFn);
    }
protected:
    inline FunctionCallerBase* GuardFunctor() const
    {
        return guardFunctorPtr;
    }

    inline FunctionCallerBase* OnTransitionActionFunctor() const
    {
        return onTransitionActionPtr;
    }
    // users must be re-implement these functions for own requirements
    virtual bool eventTest(QEvent *event) = 0;
    virtual void onTransition(QEvent *event) = 0;
};

class RhapsodyEventTransition : public RhTransitionOverrides<QAbstractTransition>
{
public:
    RhapsodyEventTransition(short evID,
                            QState *sourceState,
                            QState *targetState = 0) :
        RhTransitionOverrides(sourceState), id_(evID)
    {
        if (targetState) setTargetState(targetState);
    }

private:
    bool eventTest(QEvent *event) // override
    {
        if (event->type() != QEvent::Type(QEvent::User + EvDispatcherHelperOffset) ||
            static_cast<EventDispatcherHelper*>(event)->getId() != id_)
            return false;
        if (GuardFunctor())
            return GuardFunctor()->CallFunc(this, event);
        else
            return true;
    }

    void onTransition(QEvent *event) // override
    {
        Q_ASSERT(static_cast<EventDispatcherHelper*>(event)->getId() == id_);
        if (OnTransitionActionFunctor())
            OnTransitionActionFunctor()->CallFunc(this, event);
    }
protected:
    inline void setId(short id)
    {
        id_ = id;
    }
    inline short getId() const
    {
        return id_;
    }
private:
    short id_;
};

class RhapsodySignalTransition : public RhTransitionOverrides<QSignalTransition>
{
public:
    RhapsodySignalTransition(QObject *sender, const char *signal,
                             QState *sourceState = 0) :
        RhTransitionOverrides(sender, signal, sourceState) { }
private:
    bool eventTest(QEvent *event) // override
    {
        if (!QSignalTransition::eventTest(event)) return false;
        if (GuardFunctor())
            return GuardFunctor()->CallFunc(this, event);
        else
            return true;
    }

    void onTransition(QEvent *event) // override
    {
        QSignalTransition::onTransition(event);
        if (OnTransitionActionFunctor())
            OnTransitionActionFunctor()->CallFunc(this, event);
    }
};

#endif // RHTRANSITIONS_HPP
