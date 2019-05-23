#ifndef IHABERLESMEYONETICISI_H
#define IHABERLESMEYONETICISI_H

#include <QObject>

class IHaberlesmeYoneticisi
{
public:
    IHaberlesmeYoneticisi();
    virtual ~IHaberlesmeYoneticisi() = 0;
    virtual void Foo(int x) = 0;
};

#endif // IHABERLESMEYONETICISI_H
