#include <QCoreApplication>
#include <QPointer>
#include <QTimer>
#include <QDebug>
#include <kroki/KrokiBilgiServisi.h>
#include <kroki/KrokiYoneticisi.h>
#include <kroki/CompositeInterfaceClass.h>
#include <kroki/HaberlesmeYoneticisi.h>
#include <Rh/QRhapsodyInitializer.h>

int main(int argc, char *argv[])
{
    //_ASSERT(false);
    int res = 0;
    {
        qDebug() << "\n\n" << __FUNCTION__ << "thread: " << QThread::currentThreadId() << "\n";

        QCoreApplication a(argc, argv);
        KrokiBilgiServisi krokiservis;
        KrokiYoneticisi krokiyonetici;
        CompositeInterfaceClass ci;
        HaberlesmeYoneticisi hy;
        QObject::connect(&hy, SIGNAL(signalVeriKanaliniKapat()), &ci, SLOT(slotHaberlesmeYoneticisi()));

        krokiservis.basla();
        krokiyonetici.basla();

        QRhapsodyInitializer::instance()->InitializationDone();

        krokiyonetici.MesafeKartiTalebi();

        krokiservis.KYKrokiTalebi(0);
        QTimer::singleShot(15000, &a, SLOT(quit()));
        res = a.exec();
    }

    qDebug("Apllication done.. Press Enter to exit.");
    //getchar();
    return res;
}
