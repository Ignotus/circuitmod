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
    
    ICircuitView *view = NULL;
    if (info == typeid(And2))
        view = new And2View(m_view);
    else if (info == typeid(NAnd2))
        view = new Nand2View(m_view);
    else if (info == typeid(NOr2))
        view = new Nor2View(m_view);
    else if (info == typeid(Or2))
        view = new Or2View(m_view);
    else if (info == typeid(Not))
        view = new NotView(m_view);
    else if (info == typeid(Input))
        view = new InputView(m_view);
    else if (info == typeid(Output))
        view = new OutputView(m_view);
        
    view->setModel(model);
    return view;
}