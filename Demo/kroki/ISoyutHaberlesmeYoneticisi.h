#ifndef ISOYUTHABERLESMEYONETICISI_H
#define ISOYUTHABERLESMEYONETICISI_H

#include <QObject>

class ISoyutHaberlesmeYoneticisi : public QObject
{
    Q_OBJECT
public:
    explicit ISoyutHaberlesmeYoneticisi(QObject *parent = 0);
    virtual ~ISoyutHaberlesmeYoneticisi() = 0;

    void gonder(void* bilgi);
protected:
    virtual void bilgiUret(int baglantiNumarasi) = 0;
signals:
    void signalVeriKanaliniKapat();
public slots:
};

#endif // ISOYUTHABERLESMEYONETICISI_H
