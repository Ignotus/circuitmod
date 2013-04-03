#include <stdexcept>
#include <QStringList>
#include <QDebug>
#include "icircuit.h"

ICircuit::ICircuit()
    : QObject(0)
    , m_firstCall(true)
{
}

void ICircuit::setIO(const StateMap& inputValues, const StateMap& outputValues)
{
    m_inputs = inputValues;
    m_outputs = outputValues;
}

QList<QString> ICircuit::inputs() const
{
    return m_inputs.keys();
}

QList<QString> ICircuit::outputs() const
{
    return m_outputs.keys();
}

QPair<bool, IOType> ICircuit::find(const QString& name) const
{
    if (m_inputs.find(name) != m_inputs.end())
        return qMakePair(true, INPUT);
    
    if (m_outputs.find(name) != m_outputs.end())
        return qMakePair(true, OUTPUT);
    
    return qMakePair(false, UNKNOWN);
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
        if (it != m_outputs.end())
        {
            if (it.value() == value && !m_firstCall)
                return;
            
            it.value() = value;
            m_firstCall = false;
            
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

QPair<QString, int> ICircuit::parseName(const QString& name)
{
    const QStringList& es = name.split('_');
    return qMakePair(es[0], es[1].toInt());
}

void ICircuit::subscribe(const QString& output, const CircuitSlot& slot)
{
    if (m_outputs.contains(output))
    {
        qDebug() << Q_FUNC_INFO << "Subscribing signal" << output << "in" << id();
        m_subscribers.insertMulti(output, slot);
    }
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
