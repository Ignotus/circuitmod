#pragma once
#include <QString>
#include "typedefs.h"

class IConfig
{
public:
    const StateMap& inputs() const;
    const StateMap& outputs() const;
    
    QString key(const QString& name) const;

    int incCount();
    int id() const;
protected:
    IConfig();

    void declareOutput(const QString& name);
    void declareInput(const QString& name);
    
protected:
    static int m_count;
    int m_id;
private:
    StateMap m_inputs;
    StateMap m_outputs;
    
    
private:
    IConfig(const IConfig&);
    const IConfig& operator=(const IConfig&);
    
    template<class T>
    friend void declareIO(IConfig&);
};

template<class T>
void declareIO(IConfig& config);

template<class T>
class Config : public IConfig
{
public:
    Config()
        : IConfig()
    {
        declareIO<T>(*this);
    }
};
