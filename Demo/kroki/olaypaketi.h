#ifndef OLAYPAKETI_H
#define OLAYPAKETI_H

#include <oxf/event.h>
#include <QString>


class evKBSKrokiGonder : public EventDispatcherHelper
{
public:
    evKBSKrokiGonder(QString _s) : s(_s) {
        setId(10);
    }

    EventDispatcherHelper *Clone(EventDispatcherHelper const*t)
    {
        return new evKBSKrokiGonder(static_cast<evKBSKrokiGonder const*>(t)->s);
    }
    QString s;
};

class evKYMesafeKartiTalebi : public EventDispatcherHelper
{
public:
    evKYMesafeKartiTalebi(int i) : _i(i) {
        setId(11);
    }

    EventDispatcherHelper *Clone(EventDispatcherHelper const*t)
    {
        return new evKYMesafeKartiTalebi(static_cast<evKYMesafeKartiTalebi const*>(t)->_i);
    }
    int _i;
};

#endif // OLAYPAKETI_H
