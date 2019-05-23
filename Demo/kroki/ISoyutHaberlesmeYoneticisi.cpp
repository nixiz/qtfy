#include "ISoyutHaberlesmeYoneticisi.h"

ISoyutHaberlesmeYoneticisi::ISoyutHaberlesmeYoneticisi(QObject *parent) : QObject(parent)
{

}
ISoyutHaberlesmeYoneticisi::~ISoyutHaberlesmeYoneticisi() {
}

void ISoyutHaberlesmeYoneticisi::gonder(void* bilgi)
{
    Q_UNUSED(bilgi);
    emit signalVeriKanaliniKapat();
}
