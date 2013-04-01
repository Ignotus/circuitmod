#include "icircuitview.h"
#include "typedefs.h"
#include "editorview.h"

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

void ICircuitView::drawRectangle(const QPoint& center, int padding) const
{
    glBegin(GL_QUADS);
        glVertex2d(center.x() - padding, center.y() - padding);
        glVertex2d(center.x() + padding, center.y() - padding);
        glVertex2d(center.x() + padding, center.y() + padding);
        glVertex2d(center.x() - padding, center.y() + padding);
    glEnd();
}

void ICircuitView::drawInputWire(const QPoint& end) const
{
    drawLine({end.x() - WIRE_LENGTH, end.y()}, end);
}

void ICircuitView::drawOutputWire(const QPoint& begin) const
{
    drawLine(begin, {begin.x() + WIRE_LENGTH, begin.y()});
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

void ICircuitView::drawText(const QPoint& begin, const QString& text) const
{
    m_editor->renderText(begin.x(), begin.y(), text);
}

void ICircuitView::drawLine(const QPoint& first, const QPoint& second) const
{
    glVertex2d(first.x(), first.y());
    glVertex2d(second.x(), second.y());
}

void ICircuitView::qglColor(const QColor& c) const
{
    m_editor->qglColor(c);
}
    
QIcon ICircuitView::icon() const
{
    return QIcon();
}
