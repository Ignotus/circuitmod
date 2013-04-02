#include "icircuitview.h"
#include "typedefs.h"
#include "editorview.h"
#include "icircuit.h"
#include "drawinghelper.h"

ICircuitView::ICircuitView(EditorView *parent)
    : QObject(parent)
    , m_editor(parent)
{
}

void ICircuitView::setBeginPoint(const QPoint& begin)
{
    m_begin = begin;
}

void ICircuitView::setModel(ICircuit *model)
{
    m_model = model;
}

void ICircuitView::select()
{
    m_isSelected = true;
}

void ICircuitView::unselect()
{
    m_isSelected = false;
}

void ICircuitView::draw()
{
    if (m_isSelected)
        drawBorder();
    
    DrawingHelper::drawText({m_begin.x(), m_begin.y() + CIRCUIT_HEIGHT + 10},
                             "E" + QString::number(m_model->id()), m_editor);
}

EditorView* ICircuitView::editor() const
{
    return m_editor;
}

void ICircuitView::setMousePosition(const QPoint& pos)
{
    m_mousePosition = pos;
}

bool ICircuitView::isSelected() const
{
    return m_isSelected;
}

const QPoint& ICircuitView::beginPoint() const
{
    return m_begin;
}

const QPoint& ICircuitView::mousePosition() const
{
    return m_mousePosition;
}

QPolygon ICircuitView::border() const
{
    const QPolygon poly({m_begin,
        {m_begin.x() + CIRCUIT_WIDTH, m_begin.y()},
        {m_begin.x() + CIRCUIT_WIDTH, m_begin.y() + CIRCUIT_HEIGHT / 2},
        {m_begin.x() + CIRCUIT_WIDTH, m_begin.y() + CIRCUIT_HEIGHT},
        {m_begin.x(), m_begin.y() + CIRCUIT_HEIGHT},
        {m_begin.x(), m_begin.y() + CIRCUIT_HEIGHT / 2}
    });
    return poly;
}