#pragma once
#include <functional>
#include <QMap>
#include "circuitslot.h"
#include "config.h"
#include "typedefs.h"

class ICircuit
{
public:
    ICircuit(const StateMap& inputValues, const StateMap& outputValues);
    virtual ~ICircuit() {}
    
    QList<QString> inputs() const;
    QList<QString> outputs() const;

    bool state(const QString& name) const;

    bool operator[](const QString& name) const;

    bool setSignal(const QString& name, bool value);
    
    void subscribe(const QString& output, const CircuitSlot& slot);
    void unsubscribe(const QString& output, const CircuitSlot& slot);
    void unsubscribe(const CircuitSlot& slot);

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
    public: \
        CLASS_NAME(); \
        virtual ~CLASS_NAME(); \
        QString key(const QString& name) const; \
    private: \
        virtual void update();\
    }
    
#define DECLARE_CIRCUIT_CLASS_IMPL(CLASS_NAME) \
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

