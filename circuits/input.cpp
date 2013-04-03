#include <QVector>
#include <QTimer>
#include "input.h"

Input::Input()
    : ICircuit()
{
    setIO(m_config.inputs(), m_config.outputs());
}

int Input::id() const
{
    return m_config.id();
}

void Input::update()
{
}

void Input::onSignal(bool value)
{
    setState("IN_" + QString::number(id()), value);
}


template<>
void declareIO<Input>(IConfig& config)
{
    config.declareOutput("IN");
}

