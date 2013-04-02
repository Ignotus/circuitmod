#include "icircuit.h"
#include "editormodel.h"
#include "circuits/circuits.h"

EditorModel::EditorModel()
{

}

EditorModel::~EditorModel()
{
}

ICircuit* EditorModel::construct(const QString& name)
{
    if (name == typeid(And2).name())
        return new And2;
    
    if (name == typeid(NAnd2).name())
        return new NAnd2;
    
    if (name == typeid(NOr2).name())
        return new NOr2;
    
    if (name == typeid(Or2).name())
        return new Or2;
    
    if (name == typeid(Not).name())
        return new Not;
    
    return NULL;
}

EditorModel::CircuitCollection& EditorModel::circuits()
{
    return m_circuits;
}

const EditorModel::CircuitCollection& EditorModel::circuits() const
{
    return m_circuits;
}

void EditorModel::add(ICircuit *circuit)
{
    m_circuits[circuit->id()].reset(circuit);
}

void EditorModel::remove(int id)
{
    m_circuits.remove(id);
}

