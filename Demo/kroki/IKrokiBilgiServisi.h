/*********************************************************************
	Rhapsody	: 7.5.1 
	Login		: okatli
	Component	: AGAMA 
	Configuration 	: windows
	Model Element	: IKrokiBilgiServisi
//!	Generated Date	: Tue, 18, Dec 2018  
	File Path	: AGAMA\windows\IKrokiBilgiServisi.h
*********************************************************************/

#ifndef IKrokiBilgiServisi_H
#define IKrokiBilgiServisi_H

#include <QObject>
#include <QString>

//## class IKrokiBilgiServisi
// Kroki bilgi servisi arayüz sýnýfýdýr.
class IKrokiBilgiServisi {
    ////    Constructors and destructors    ////
public :
    //## auto_generated
    IKrokiBilgiServisi();

    //## auto_generated
    virtual ~IKrokiBilgiServisi() = 0;

    ////    Operations    ////
    
    virtual bool durumHaritalariniSil() = 0;
    virtual void krokileriSil() = 0;
    virtual void KYKrokiTalebi(int id) = 0;
    virtual void KYMesafeKartiTalebi(int id) = 0;
    virtual void QRAGUIBrifingAc(QString ad) = 0;
    virtual void QRAGUIKrokiTalebi(int id) = 0;
};

//SAVE_INTERFACE(IKrokiBilgiServisi);

#endif
/*********************************************************************
	File Path	: AGAMA\windows\IKrokiBilgiServisi.h
*********************************************************************/
