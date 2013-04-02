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

