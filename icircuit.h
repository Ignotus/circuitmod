#pragma once
#include <functional>
#include <QMap>
#include "circuitslot.h"
#include "config.h"
#include "typedefs.h"

class ICircuit
{
public:
    ICircuit();
    virtual ~ICircuit() {}
    
    void setIO(const StateMap& inputValues, const StateMap& outputValues);
    QList<QString> inputs() const;
    QList<QString> outputs() const;

    bool state(const QString& name) const;

    bool operator[](const QString& name) const;

    bool setSignal(const QString& name, bool value);
    
    void subscribe(const QString& output, const CircuitSlot& slot);
    void unsubscribe(const QString& output, const CircuitSlot& slot);
    void unsubscribe(const CircuitSlot& slot);
    virtual int id() const = 0;

protected:
    void setState(const QString& name, bool value);
    
private:
    virtual void update() = 0;

private:
    StateMap m_inputs;
    StateMap m_outputs;
    
    QMultiMap<QString, CircuitSlot> m_subscribers;
};

#define DECLARE_CIRCUIT_CLASS(CLASS_NAME) \
    class CLASS_NAME : public ICircuit \
    { \
        Config<CLASS_NAME> m_config;\
    public: \
        CLASS_NAME(); \
        virtual ~CLASS_NAME(); \
        int id() const; \
        QString key(const QString& name) const; \
    private: \
        void update();\
    }
    
#define DECLARE_CIRCUIT_CLASS_IMPL(CLASS_NAME) \
    CLASS_NAME::CLASS_NAME() \
        : ICircuit() \
    { \
        setIO(m_config.inputs(), m_config.outputs());\
    } \
    CLASS_NAME::~CLASS_NAME() {} \
    \
    QString CLASS_NAME::key(const QString& name) const \
    {\
        return m_config.key(name); \
    }\
    \
    int CLASS_NAME::id() const \
    {\
        return m_config.id();\
    }\
    void CLASS_NAME::update()

