#pragma once
#include <QString>
#include "icircuit.h"

class IConfig;
template<class T>
void declareIO(IConfig& config);

class IConfig
{
public:
    const ICircuit::StateMap& inputs() const;
    const ICircuit::StateMap& outputs() const;
    
    QString key(const QString& name) const;

protected:
    IConfig();

    void declareOutput(const QString& name);
    void declareInput(const QString& name);
    
protected:
    static int m_count;
    int m_id;

private:
    ICircuit::StateMap m_inputs;
    ICircuit::StateMap m_outputs;
    
    
private:
    IConfig(const IConfig&);
    const IConfig& operator=(const IConfig&);
    
    template<class T>
    friend void declareIO(IConfig&);
};

template<class T>
class Config : public IConfig
{
public:
    static Config<T>& instance()
    {
        static Config<T> obj;
        return obj;
    }
    
private:
    Config()
        : IConfig()
    {
        declareIO<T>(*this);
    }
};