/*
 * QRhapsodyInitializer.h
 *  
 * Copyright (C) Oguzhan KATLI
 * All Rights Reserved
 *
 * See the LICENSE file for the terms of usage and distribution.
 *
 */
#ifndef QRHAPSODYINITIALIZER_H
#define QRHAPSODYINITIALIZER_H

#include <QObject>

class QRhapsodyInitializer : public QObject
{
    Q_OBJECT
private:
    explicit QRhapsodyInitializer();

public:
    ~QRhapsodyInitializer();
    static QRhapsodyInitializer* instance();
    void InitializationDone();
signals:
    void ConstructionObjectsDone();

public slots:
};

#endif // QRHAPSODYINITIALIZER_H
