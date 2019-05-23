/*********************************************************************
	Rhapsody	: 7.5.1 
	Login		: okatli
	Component	: AGAMA 
	Configuration 	: windows
	Model Element	: IKrokiYoneticisi
//!	Generated Date	: Tue, 18, Dec 2018  
	File Path	: AGAMA\windows\IKrokiYoneticisi.h
*********************************************************************/

#ifndef IKrokiYoneticisi_H
#define IKrokiYoneticisi_H

#include <QObject>
#include <QString>

//## class IKrokiYoneticisi
// Kroki yöneticisi arayüz sýnýfýdýr.
class IKrokiYoneticisi {
    ////    Constructors and destructors    ////

public :

    //## auto_generated
    IKrokiYoneticisi();

    //## auto_generated
    virtual ~IKrokiYoneticisi() = 0;

    virtual void KBSKrokiGonder(const QString& yeniKroki) = 0;
    virtual void QRAKrokiMesajGonder(int id) = 0;
};

//SAVE_INTERFACE(IKrokiYoneticisi);

#endif
/*********************************************************************
	File Path	: AGAMA\windows\IKrokiYoneticisi.h
*********************************************************************/
