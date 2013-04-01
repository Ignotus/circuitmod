#pragma once
#include <vector>
#include <memory>

class ICircuit;
class QString;
class EditorModel 
{
public:
    typedef std::vector<std::unique_ptr<ICircuit> > CircuitVector;
public:
    EditorModel();
    virtual ~EditorModel();
    
    void add(ICircuit *circuit);
    EditorModel::CircuitVector::iterator remove(CircuitVector::iterator it);
   
    CircuitVector& circuits();
    const CircuitVector& circuits() const;
   
    static ICircuit* construct(const QString& name);
private:
    CircuitVector m_circuits;
};
