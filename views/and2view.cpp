#include <QtOpenGL>
#include <QDebug>
#include "and2view.h"
#include "typedefs.h"
#include "editorview.h"

And2View::And2View(EditorView *parent)
    : ICircuitView(parent)
{
}

void And2View::draw()
{
    const QPoint second{m_begin.x() + CIRCUIT_WIDTH, m_begin.y()};
    const QPoint third{m_begin.x() + CIRCUIT_WIDTH, m_begin.y() + CIRCUIT_HEIGHT};
    const QPoint fourth{m_begin.x(), m_begin.y() + CIRCUIT_HEIGHT};
    
    glBegin(GL_POLYGON);
        qglColor(Qt::white);
        glVertex2d(m_begin.x(), m_begin.y());
        glVertex2d(second.x(), second.y());
        glVertex2d(third.x(), third.y());
        glVertex2d(fourth.x(), fourth.y());
    glEnd();
    
    glBegin(GL_LINES);
        qglColor(Qt::black);
        drawLine(m_begin, second);
        drawLine(second, third);
        drawLine(third, fourth);
        drawLine(fourth, m_begin);
       
        drawOutputWire({second.x(), second.y() + CIRCUIT_HEIGHT / 2});
        drawInputWire({m_begin.x(), m_begin.y() + CIRCUIT_HEIGHT / 4});
        drawInputWire({m_begin.x(), m_begin.y() + CIRCUIT_HEIGHT * 3 / 4});
    glEnd();
    
    drawText(QPoint(m_begin.x() + CIRCUIT_WIDTH / 2, m_begin.y() + CIRCUIT_HEIGHT / 2), "&");
    
    ICircuitView::draw();
}

void And2View::drawBorder()
{
    const QPolygon& poly = border();
    
    foreach (const QPoint& point, poly)
    {
        qglColor(Qt::black);
        drawRectangle(point, 3);
        qglColor(Qt::green);
        drawRectangle(point, 2);
    }
}
