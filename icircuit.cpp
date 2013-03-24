#include <stdexcept>
#include "icircuit.h"

ICircuit::ICircuit(const StateMap& inputValues, const StateMap& outputValues)
    : m_inputs(inputValues)
    , m_outputs(outputValues)
{
}

QList<QString> ICircuit::inputs() const
{
    return m_inputs.keys();
}

QList<QString> ICircuit::outputs() const
{
    return m_outputs.keys();
}

bool ICircuit::state(const QString& name) const
{
    StateMap::ConstIterator it = m_inputs.find(name);
    bool isFound = (it != m_inputs.end());

    if (!isFound)
    {
        it = m_outputs.find(name);
        isFound = (it != m_outputs.end());
    }

    if (isFound)
        return it.value();
    
    throw std::logic_error(QString("Input or output not found: %1").arg(name).toStdString());
}

bool ICircuit::operator[](const QString& name) const
{
    return state(name);
}

void ICircuit::setState(const QString& name, bool value)
{
    StateMap::Iterator it = m_inputs.find(name);
    if (it != m_inputs.end())
    {
        it.value() = value;
    }
    else
    {
        it = m_outputs.find(name);
        if (it != m_inputs.end())
        {
            it.value() = value;

            emit onOutputChanged(name, value);
        }
    }
}

bool ICircuit::setSignal(const QString& name, bool value) {
    StateMap::Iterator it = m_inputs.find(name);
    if (it != m_inputs.end())
    {
        it.value() = value;
        
        update();
    }
    
    return false;
}


int IConfig::m_count = 0;

IConfig::IConfig()
    : boost::noncopyable()
{
    ++m_count;
    m_id = m_count;
}

QString IConfig::key(const QString& name) const
{
    return name + QString::number(m_id);
}

const ICircuit::StateMap& IConfig::inputs() const
{
    return m_inputs;
}

const ICircuit::StateMap& IConfig::outputs() const
{
    return m_outputs;
}
