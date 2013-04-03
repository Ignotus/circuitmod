#include "icircuit.h"
#include "editormodel.h"
#include "circuits/circuits.h"

EditorModel::EditorModel()
    : QObject(0)
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
    
    if (name == typeid(Input).name())
        return new Input;
    
    if (name == typeid(Output).name())
        return new Output;
    
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

EditorModel::CircuitCollection& EditorModel::inputs()
{
    return m_inputs;
}

void EditorModel::add(ICircuit *circuit)
{
    std::shared_ptr<ICircuit> ptr(circuit);
    Input *input = qobject_cast<Input*>(circuit);
    if (input != NULL)
    {
        m_inputs[input->id()] = ptr;
    }
    else
    {
        Output *output = qobject_cast<Output*>(circuit);
        if (output != NULL)
        {
            m_outputs[output->id()] = ptr;
            connect(output, SIGNAL(signalChanged(int, bool)),
                    this, SIGNAL(signalChanged(int, bool)));
        }
    }
    m_circuits[circuit->id()] = ptr;
}

void EditorModel::remove(int id)
{
    m_circuits.remove(id);
    m_inputs.remove(id);
    m_outputs.remove(id);
}

