#pragma once
#include <map>
#include <functional>
#include <type_traits>

#include <boost/noncopyable.hpp>

#include <QObject>
#include <QMap>
#include <QPair>

class ICircuit : public QObject
{
    Q_OBJECT
public:
    typedef QMap<QString, bool> StateMap;

public:
    ICircuit(const StateMap& inputValues, const StateMap& outputValues);
    virtual ~ICircuit() {}
    
    QList<QString> inputs() const;
    QList<QString> outputs() const;

    bool state(const QString& name) const;

    bool operator[](const QString& name) const;

public slots:
    bool setSignal(const QString& name, bool value);

signals:
    void onOutputChanged(const QString& name, bool value);

protected:
    void setState(const QString& name, bool value);
    
private:
    virtual void update() = 0;

private:
    StateMap m_inputs;
    StateMap m_outputs;
};

class IConfig;
template<class T>
void declareIO(IConfig& config);

class IConfig : public boost::noncopyable
{
public:
    const ICircuit::StateMap& inputs() const;
    const ICircuit::StateMap& outputs() const;
    
    QString key(const QString& name) const;

protected:
    IConfig();

    void declareOutput(const QString& name)
    {
        m_outputs[key(name)] = false;
    }
    
    void declareInput(const QString& name)
    {
        m_inputs[key(name)] = false;
    }
    
protected:
    static int m_count;
    int m_id;

private:
    ICircuit::StateMap m_inputs;
    ICircuit::StateMap m_outputs;
    
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

#define DECLARE_CIRCUIT_CLASS(CLASS_NAME) \
    class CLASS_NAME : public ICircuit \
    { \
    public: \
        CLASS_NAME(); \
        virtual ~CLASS_NAME(); \
    \
    private: \
        QString key(const QString& name) const; \
        virtual void update(); \
    };\
    CLASS_NAME::CLASS_NAME() \
        : ICircuit(Config<CLASS_NAME>::instance().inputs(), \
                   Config<CLASS_NAME>::instance().outputs()) \
    { \
    } \
    CLASS_NAME::~CLASS_NAME() {} \
    \
    QString CLASS_NAME::key(const QString& name) const \
    {\
        return Config<CLASS_NAME>::instance().key(name); \
    }\
    void CLASS_NAME::update()

