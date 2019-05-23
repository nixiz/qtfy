#include "QRhapsodyInitializer.h"

QRhapsodyInitializer::QRhapsodyInitializer()
{

}

QRhapsodyInitializer::~QRhapsodyInitializer()
{
}

// static
QRhapsodyInitializer* QRhapsodyInitializer::instance()
{
    static QRhapsodyInitializer self;
    return &self;
}

void QRhapsodyInitializer::InitializationDone()
{
    emit ConstructionObjectsDone();
}
