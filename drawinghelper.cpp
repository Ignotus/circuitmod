#include <QtOpenGL>
#include "drawinghelper.h"
#include "editorview.h"
#include "typedefs.h"

namespace
{
    void setColor(const QColor& color)
    {
        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    }
}

void DrawingHelper::drawPolygon(const QPolygon& poly, const QColor& color) 
{
    glBegin(GL_POLYGON);
        setColor(color);
        foreach (const QPoint& point, poly)
            glVertex2d(point.x(), point.y());
    glEnd();
}

void DrawingHelper::drawRectangle(const QPoint& center, int padding, const QColor& color) 
{
    glBegin(GL_QUADS);
        setColor(color);
        glVertex2d(center.x() - padding, center.y() - padding);
        glVertex2d(center.x() + padding, center.y() - padding);
        glVertex2d(center.x() + padding, center.y() + padding);
        glVertex2d(center.x() - padding, center.y() + padding);
    glEnd();
}

void DrawingHelper::drawInputWire(const QPoint& end, const QColor& color) 
{
    drawLine({end.x() - WIRE_LENGTH, end.y()}, end, color);
}

void DrawingHelper::drawOutputWire(const QPoint& begin, const QColor& color) 
{
    drawLine(begin, {begin.x() + WIRE_LENGTH, begin.y()}, color);
}

void DrawingHelper::drawWire(const QPoint& first, const QPoint& second, const QColor& color)
{
    if (first.x() < second.x())
    {
        if (first.y() == second.y())
            drawLine(first, second, color);
        else
        {
            const int x = (second.x() + first.x()) / 2;
            
            drawLine({x, std::min(second.y(), first.y())}, {x, std::max(second.y(), first.y())}, color);
            drawLine({x, first.y()}, first, color);
            drawLine({x, second.y()}, second, color);
        }
    }
    else if (first.x() > second.x())
    {
        int y;
        const int firstx = first.x() + 10;
        const int secondx = second.x() - 10;
        
        if (first.x() - second.x() < CIRCUIT_WIDTH + 2 * WIRE_LENGTH + 20)
        {
            y = (first.y() + second.y()) / 2;
        }
        else if (first.y() <= second.y())
        {
            y = first.y() - CIRCUIT_HEIGHT;
            if (y <= 0)
                y = first.y() + CIRCUIT_HEIGHT;
        }
        else
        {
            y = first.y() + CIRCUIT_HEIGHT;
        }

        drawLine(first, {firstx, first.y()}, color);
        drawLine(second, {secondx, second.y()}, color);
        drawLine({firstx, first.y()}, {firstx, y}, color);
        drawLine({secondx, second.y()}, {secondx, y}, color);
        drawLine({firstx, y}, {secondx, y}, color);
    }
}

void DrawingHelper::drawLine(const QPoint& first, const QPoint& second, const QColor& color)
{
    glBegin(GL_LINES);
        setColor(color);
        glVertex2d(first.x(), first.y());
        glVertex2d(second.x(), second.y());
    glEnd();
}

namespace
{
    QPolygon::const_iterator next(QPolygon::const_iterator current, const QPolygon& poly)
    {
        if (++current == poly.end())
            return poly.begin();
        else
            return current;
    }
}

void DrawingHelper::drawPolygonBorder(const QPolygon& poly, const QColor& color)
{
    glBegin(GL_LINES);
        setColor(color);
        for (QPolygon::const_iterator it = poly.begin(), end = poly.end();
            it != end;
            ++it)
        {
            QPolygon::const_iterator ne = next(it, poly);
            
            glVertex2d(it->x(), it->y());
            glVertex2d(ne->x(), ne->y());
        }
    glEnd();
}

void DrawingHelper::drawText(const QPoint& begin, const QString& text,
                             EditorView *view, const QColor& color)
{
    setColor(color);
    view->renderText(begin.x(), begin.y(), text);
}