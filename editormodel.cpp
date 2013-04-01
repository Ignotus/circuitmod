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

EditorModel::CircuitVector& EditorModel::circuits()
{
    return m_circuits;
}

const EditorModel::CircuitVector& EditorModel::circuits() const
{
    return m_circuits;
}

void EditorModel::add(ICircuit *circuit)
{
    m_circuits.push_back(std::unique_ptr<ICircuit>(circuit));
}

EditorModel::CircuitVector::iterator EditorModel::remove(EditorModel::CircuitVector::iterator it)
{
    return m_circuits.erase(it);
}

