#include <QDebug>
#include "elementadder.h"
#include "icircuit.h"
#include "editormodel.h"
#include "icircuitview.h"
#include "circuits/circuits.h"
#include "views/views.h"

ElementAdder::ElementAdder(EditorModel *em, EditorView *view)
    : m_em(em)
    , m_view(view)
{
}
    
void ElementAdder::setCurrentElement(const QString& name)
{
    m_name = name;
}

void ElementAdder::clear()
{
    m_name.clear();
}
    
bool ElementAdder::hasCurrentElement() const
{
    return !m_name.isEmpty();
}

const QString& ElementAdder::currentName() const
{
    return m_name;
}
    
ICircuitView* ElementAdder::constructCurrentView(const QPoint& begin)
{
    if (!hasCurrentElement())
        return NULL;
    
    ICircuit *c = EditorModel::construct(m_name);
        
    m_em->add(c);
    ICircuitView *v = constructCircuitView(c);
    v->setBeginPoint(begin);
    
    return v;
}

ICircuitView* ElementAdder::constructCircuitView(ICircuit *model)
{
    const std::type_info& info = typeid(*model);
    
    if (info == typeid(And2))
    {
        ICircuitView *view = new And2View(m_view);
        view->setModel(model);
        return view;
    }
    
    return NULL;
}