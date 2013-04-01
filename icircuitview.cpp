#include "icircuitview.h"

ICircuitView::ICircuitView(QWidget *parent)
    : QWidget(parent)
{
}

void ICircuitView::setModel(ICircuit *model)
{
    m_model = model;
}
    
QIcon ICircuitView::icon() const
{
    return QIcon();
}
