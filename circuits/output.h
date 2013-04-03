#pragma once
#include "icircuit.h"

class Output : public ICircuit
{
    Q_OBJECT
    Config<Output> m_config;
public:
    Output();
    
    int id() const;
    
private:
    void update();

signals:
    void signalChanged(int, bool);
};
