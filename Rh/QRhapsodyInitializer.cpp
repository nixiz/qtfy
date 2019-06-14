/*
 * QRhapsodyInitializer.cpp
 *  
 * Copyright (C) Oguzhan KATLI
 * All Rights Reserved
 *
 * See the LICENSE file for the terms of usage and distribution.
 *
 */
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
