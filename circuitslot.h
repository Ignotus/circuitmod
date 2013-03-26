#pragma once
#include <QString>

class ICircuit;
class CircuitSlot
{
public:
    CircuitSlot(ICircuit *receiver, const QString& input);
    void operator()(bool value);
    bool operator==(const CircuitSlot& other) const;
    operator bool() const;
    
private:
    ICircuit * const m_receiver;
    const QString m_input;
};