#include <QVector>
#include <QTimer>
#include "output.h"

Output::Output()
    : ICircuit()
{
    setIO(m_config.inputs(), m_config.outputs());
}

int Output::id() const
{
    return m_config.id();
}

void Output::update()
{
    emit signalChanged(id(), state("OUT_" + QString::number(id())));
}

template<>
void declareIO<Output>(IConfig& config)
{
    config.declareInput("OUT");
}

