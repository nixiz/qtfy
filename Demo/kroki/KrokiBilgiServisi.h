#ifndef KROKIBILGISERVISI_H
#define KROKIBILGISERVISI_H

#include <qtfy.hpp>
#include "IKrokiBilgiServisi.h"
#include "IKrokiYoneticisi.h"
#include "icompositeinterface.h"
#include "IHaberlesmeYoneticisi.h"
#include <oxf/omreactive.h>

class KrokiBilgiServisi : public Qtfy, public IKrokiBilgiServisi
{
    Q_OBJECT
public:
    typedef Port_T<IKrokiBilgiServisi, IKrokiYoneticisi> KrokiBilgiServisiPortu;
    typedef Port_T<EmptyType, IInterface1> InterfaceIPortu;
    DECLARE_PORT_OUT(IHaberlesmeYoneticisi) HaberlesmeYoneticisiPortu;

    explicit KrokiBilgiServisi(QObject *parent = 0);
    ~KrokiBilgiServisi();

    void basla();

    //## operation durumHaritalariniSil()
    bool durumHaritalariniSil();

public slots:
    //## operation krokileriSil()
    void krokileriSil();


    void KYKrokiTalebi(int id);
    void KYMesafeKartiTalebi(int id);
    void QRAGUIBrifingAc(QString ad);
    void QRAGUIKrokiTalebi(int id);
protected slots:
    void HandleEvent(EventDispatcherHelper* ev);
    void ServiceThreadStarted() {}
    void ServiceThreadFinished() {}
    void ServiceThreadTerminated() {}
signals:
    void krokiYoneticisineKrokiYolla(const QString&);
};

#endif // KROKIBILGISERVISI_H
