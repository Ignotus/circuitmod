#include "and2circuit.h"

namespace
{
    DECLARE_CONFIG
    {
        m_inputs[key("A")] = false;
        m_inputs[key("B")] = false;
        m_outputs[key("Q")] = false;
    }
}

And2Circuit::And2Circuit()
    : ICircuit(Config::instance().inputs(), Config::instance().outputs())
{
}

bool& And2Circuit::operator[](const QString& name)
{
    bool& res = ICircuit::operator[](name);
    
    
    
    return res;
}

bool And2Circuit::setSignal(const QString& name, bool value)
{
    return true;
}

bool And2Circuit::setSignal(const StateMap& values)
{
    return true;
}
