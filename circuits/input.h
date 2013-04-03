#pragma once
#include "icircuit.h"

class Input : public ICircuit
{
    Q_OBJECT
    Config<Input> m_config;
public:
    Input();
    
    int id() const;
    
private:
    void update();
    
public slots:
    void onSignal(bool);
};
