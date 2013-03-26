#include "circuitslot.h"
#include "icircuit.h"

CircuitSlot::CircuitSlot(ICircuit *receiver, const QString& input)
    : m_receiver(receiver)
    , m_input(input)
{   
}
    
void CircuitSlot::operator()(bool value)
{
    m_receiver->setSignal(m_input, value);
}

bool CircuitSlot::operator==(const CircuitSlot& other) const
{
    return m_receiver == other.m_receiver && m_input == other.m_input;
}

CircuitSlot::operator bool() const
{
    return m_receiver != NULL;
}