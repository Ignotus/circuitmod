#pragma once
#include <vector>
#include <memory>

class ICircuit;
class EditorModel 
{
public:
    typedef std::vector<std::unique_ptr<ICircuit> > CircuitVector;
public:
    EditorModel();
    virtual ~EditorModel();
    
    void add(ICircuit *circuit);
    void remove(int id);
    
    const CircuitVector& circuits() const;
    
private:
    CircuitVector m_circuits;
};
