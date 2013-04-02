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

namespace
{
    const int PADDING = 4;
    QPolygon polygon(const QPoint& point)
    {
        return QPolygon({
            {point + QPoint(-PADDING, -PADDING)},
            {point + QPoint(PADDING, -PADDING)},
            {point + QPoint(PADDING, PADDING)},
            {point + QPoint(-PADDING, PADDING)}

        });
    }
}

void ICircuitView::setBeginPoint(const QPoint& begin)
{
    m_begin = begin;
    
    const QList<QString>& inputs = m_model->inputs();
    const QList<QString>& outputs = m_model->outputs();
    
    if (inputs.size() == 1)
    {
        m_inputs[inputs[0]] = polygon(beginPoint() + QPoint(-WIRE_LENGTH, CIRCUIT_HEIGHT / 2));
    }
    else if (inputs.size() == 2)
    {
        m_inputs[inputs[0]] = polygon(beginPoint() + QPoint(-WIRE_LENGTH, CIRCUIT_HEIGHT / 4));
        m_inputs[inputs[1]] = polygon(beginPoint() + QPoint(-WIRE_LENGTH, CIRCUIT_HEIGHT * 3 / 4));
    }
    
    if (outputs.size() == 1)
    {
        m_outputs[outputs[0]] = polygon(beginPoint() + QPoint(CIRCUIT_WIDTH + WIRE_LENGTH, CIRCUIT_HEIGHT / 2));
    }
}

ICircuit* ICircuitView::model() const
{
    return m_model;
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

const QHash<QString, QPolygon>& ICircuitView::inputs() const
{
    return m_inputs;
}

const QHash<QString, QPolygon>& ICircuitView::outputs() const
{
    return m_outputs;
}