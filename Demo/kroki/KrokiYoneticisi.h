#ifndef KROKIYONETICISI_H
#define KROKIYONETICISI_H

#include <QObject>
#include "IKrokiYoneticisi.h"
#include "IKrokiBilgiServisi.h"
#include <qtfy.hpp>
#include <QState>

class KrokiYoneticisi : public Qtfy, public IKrokiYoneticisi
{
    Q_OBJECT
public:
    typedef Port_T<IKrokiYoneticisi, IKrokiBilgiServisi> KrokiBilgiServisiPortu;

    explicit KrokiYoneticisi(QObject *parent = 0);
    ~KrokiYoneticisi();

    // Kroki yöneticisinin baþlatýlmasýný ve ilgili sýnýflarla baðlantýlarýnýn kurulmasýný tetikler.
    void basla();

    void KrokiTalebi();
    void MesafeKartiTalebi();
    bool OnTransition(QAbstractTransition const* t, QEvent *e);
signals:
    void signalKYKrokiTalebi(int id);
    void signalKYMesafeKartiTalebi(int id);
    void evKEKB();
protected slots:
    void HandleEvent(EventDispatcherHelper* ev);
    void HandleStateEnter();
    void ServiceThreadStarted();
    void ServiceThreadFinished() {}
    void ServiceThreadTerminated() {}
    void evTransitionHandled();
public slots:
    void KBSKrokiGonder(const QString& yeniKroki);
    void QRAKrokiMesajGonder(int id);
private:
    bool TmGuardFunc(QAbstractTransition const* t, QEvent *e);
    //QStateMachine statechart;
};

#endif // KROKIYONETICISI_H
