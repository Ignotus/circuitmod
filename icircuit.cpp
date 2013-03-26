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
            
            QMultiMap<QString, CircuitSlot>::iterator i = m_subscribers.find(name);
            QMultiMap<QString, CircuitSlot>::iterator end = m_subscribers.end();
            while (i != end && i.key() == name) {
                CircuitSlot& slot = i.value();
                if (slot)
                {
                    slot(value);
                    ++i;
                }
                else
                    i = m_subscribers.erase(i);
            }
        }
    }
}

bool ICircuit::setSignal(const QString& name, bool value) {
    StateMap::Iterator it = m_inputs.find(name);
    if (it != m_inputs.end())
    {
        it.value() = value;
        
        update();
        return true;
    }
    
    return false;
}

void ICircuit::subscribe(const QString& output, const CircuitSlot& slot)
{
    if (m_outputs.contains(output))
        m_subscribers.insertMulti(output, slot);
}

void ICircuit::unsubscribe(const QString& output, const CircuitSlot& slot)
{
    m_subscribers.remove(output, slot);
}

void ICircuit::unsubscribe(const CircuitSlot& slot)
{
    QMultiMap<QString, CircuitSlot>::iterator it = m_subscribers.begin();
    QMultiMap<QString, CircuitSlot>::iterator end = m_subscribers.end();
    
    for (; it != end; ++it)
    {
        if (it.value() == slot)
        {
            it = m_subscribers.erase(it);
        }
    }
}
