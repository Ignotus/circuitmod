#pragma once
#include <QObject>

class CircuitTest : public QObject
{
    Q_OBJECT
private slots:
    void nand2Test();
    void nor2Test();
    void or2Test();
};