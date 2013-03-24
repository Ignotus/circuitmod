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

    QList<QString> inputs() const;
    QList<QString> outputs() const;

    bool state(const QString& name) const;

    virtual bool& operator[](const QString& name);

public slots:
    virtual bool setSignal(const QString& name, bool value) = 0;
    virtual bool setSignal(const StateMap& values) = 0;

signals:
    void onOutputChanged(const QString& name, bool value);

protected:
    void setState(const QString& name, bool value);

private:
    StateMap m_inputs;
    StateMap m_outputs;
};

class IConfig : public boost::noncopyable
{
public:
    const ICircuit::StateMap& inputs() const;
    const ICircuit::StateMap& outputs() const;

protected:
    IConfig();

    static QString key(const QString& name);

protected:
    static int m_count;

    ICircuit::StateMap m_inputs;
    ICircuit::StateMap m_outputs;
};

#define DECLARE_CONFIG \
    class Config : public IConfig \
    { \
    public: \
        static Config& instance() \
        { \
            static Config obj; \
            return obj; \
        } \
    private: \
        Config(); \
    }; \
    Config::Config() \
        : IConfig()
