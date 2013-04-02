#pragma once
#include <memory>
#include <QHash>

class ICircuit;
class QString;
class EditorModel 
{
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
private:
    CircuitCollection m_circuits;
};
