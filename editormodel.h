#pragma once
#include <memory>
#include <QHash>

class ICircuit;
class QString;
class EditorModel : public QObject
{
    Q_OBJECT
public:
    typedef QHash<int, std::shared_ptr<ICircuit> > CircuitCollection;
public:
    EditorModel();
    virtual ~EditorModel();
    
    void add(ICircuit *circuit);
    void remove(int id);
   
    CircuitCollection& circuits();
    const CircuitCollection& circuits() const;
   
    static ICircuit* construct(const QString& name);
    
    CircuitCollection& inputs();
signals:
    void signalChanged(int, bool);
    
private:
    CircuitCollection m_circuits;
    CircuitCollection m_outputs;
    CircuitCollection m_inputs;

};
