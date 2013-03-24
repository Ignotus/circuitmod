#pragma once
#include "icircuit.h"

class And2Circuit : public ICircuit
{
    Q_OBJECT
public:
    And2Circuit();
    
    bool& operator[](const QString& name);

public slots:
    bool setSignal(const QString& name, bool value);
    bool setSignal(const StateMap& values);
};

