#include "icircuit.h"
#include "editormodel.h"

EditorModel::EditorModel()
{

}

EditorModel::~EditorModel()
{
}

const EditorModel::CircuitVector& EditorModel::circuits() const
{
    return m_circuits;
}

void EditorModel::add(ICircuit *circuit)
{
    m_circuits.push_back(std::unique_ptr<ICircuit>(circuit));
}

void EditorModel::remove(int id)
{
    m_circuits.erase(m_circuits.begin() + id);
}

