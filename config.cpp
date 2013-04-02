#include "config.h"

int IConfig::m_count = 0;

IConfig::IConfig()
{
    ++m_count;
    m_id = m_count;
}

int IConfig::id() const
{
    return m_id;
}

const StateMap& IConfig::inputs() const
{
    return m_inputs;
}

const StateMap& IConfig::outputs() const
{
    return m_outputs;
}

int IConfig::incCount()
{
    return ++m_count;
}

QString IConfig::key(const QString& name) const
{
    return name + "_" + QString::number(m_id);
}

void IConfig::declareOutput(const QString& name)
{
    m_outputs[key(name)] = false;
}

void IConfig::declareInput(const QString& name)
{
    m_inputs[key(name)] = false;
}
