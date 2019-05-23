#ifndef OXF_OMEVENT_H
#define OXF_OMEVENT_H

#include <QEvent>
#define EvDispatcherHelperOffset 3
#define EventDispatcherHelperType QEvent::Type(QEvent::User + EvDispatcherHelperOffset)

#define GEN(ev) CallEvent(new ev)

#define OMSETPARAMS(evType) evType* params = ev->Cast<evType>();
#define IS_EVENT_TYPE_OF(evid) ev->getId() == evid

class EventDispatcherHelper : public QEvent
{
public:
    EventDispatcherHelper() :
        QEvent(EventDispatcherHelperType),
        id_(-1) {}

    virtual ~EventDispatcherHelper() {}
    virtual EventDispatcherHelper *Clone(EventDispatcherHelper const*) {
        return new EventDispatcherHelper;
    }

    inline short getId() const { return id_; }

    template <class Derived>
    inline Derived * Cast()
    {
        return static_cast<Derived*>(this);
    }
    inline void setId(short id) { id_ = id; }
private:
    short id_;
    Q_DISABLE_COPY(EventDispatcherHelper)
};

#if QT_VERSION_MAJOR <= 4
#include <QMetaType>
// Template specialization for EventDispatcherHelper for calling QMetaObject::invokeMethod()
// used in file: <qmetatype.h> line: 156 func: qRegisterMetaType
template <>
inline void *qMetaTypeConstructHelper(const EventDispatcherHelper* t)
{
    if (!t)
        return new EventDispatcherHelper;
    return const_cast<EventDispatcherHelper*>(t)->Clone(t);
}
#endif
typedef EventDispatcherHelper OMEvent;

#endif
