#pragma once
#include <map>

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

class IConfig : public boost::noncopyable
{
public:
    const ICircuit::StateMap& inputs() const;
    const ICircuit::StateMap& outputs() const;
    
    QString key(const QString& name) const;

protected:
    IConfig();

protected:
    static int m_count;
    int m_id;

    ICircuit::StateMap m_inputs;
    ICircuit::StateMap m_outputs;
};

#define CONFIG(CLASS_NAME) Config##CLASS_NAME::instance()

#define DECLARE_CIRCUIT_CLASS(CLASS_NAME) \
    class CLASS_NAME : public ICircuit \
    { \
    public: \
        CLASS_NAME(); \
        virtual ~CLASS_NAME(); \
    \
    private: \
        virtual void update(); \
    };\
    CLASS_NAME::CLASS_NAME() \
        : ICircuit(CONFIG(CLASS_NAME).inputs(), CONFIG(CLASS_NAME).outputs()) \
    { \
    } \
    CLASS_NAME::~CLASS_NAME() {} \
    \
    void CLASS_NAME::update()
        

#define DECLARE_CONFIG(CLASS_NAME) \
    class Config##CLASS_NAME : public IConfig \
    { \
    public: \
        static Config##CLASS_NAME& instance() \
        { \
            static Config##CLASS_NAME obj; \
            return obj; \
        } \
    private: \
        Config##CLASS_NAME(); \
    }; \
    Config##CLASS_NAME::Config##CLASS_NAME() \
        : IConfig()

        
#define KEY(CLASS_NAME, value) CONFIG(CLASS_NAME).key(value)
