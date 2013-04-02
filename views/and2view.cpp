#include <QtOpenGL>
#include <QDebug>
#include "and2view.h"
#include "typedefs.h"
#include "editorview.h"
#include "drawinghelper.h"

And2View::And2View(EditorView *parent)
    : ICircuitView(parent)
{
}

void And2View::draw()
{
    const QPoint& begin = beginPoint();
    const QPoint second{begin.x() + CIRCUIT_WIDTH, begin.y()};
    const QPoint third{begin.x() + CIRCUIT_WIDTH, begin.y() + CIRCUIT_HEIGHT};
    const QPoint fourth{begin.x(), begin.y() + CIRCUIT_HEIGHT};
    
    DrawingHelper::drawPolygon(QPolygon({begin, second, third, fourth}), Qt::white);
    DrawingHelper::drawPolygonBorder(QPolygon({begin, second, third, fourth}), Qt::black);
    
    DrawingHelper::drawOutputWire({second.x(), second.y() + CIRCUIT_HEIGHT / 2});
    DrawingHelper::drawInputWire({begin.x(), begin.y() + CIRCUIT_HEIGHT / 4});
    DrawingHelper::drawInputWire({begin.x(), begin.y() + CIRCUIT_HEIGHT * 3 / 4});
    
    DrawingHelper::drawText(QPoint(begin.x() + CIRCUIT_WIDTH / 2, begin.y() + CIRCUIT_HEIGHT / 2),
                            "&", editor());
    
    ICircuitView::draw();
}

void And2View::drawBorder()
{
    foreach (const QPoint& point, border())
    {
        DrawingHelper::drawRectangle(point, 3, Qt::black);
        DrawingHelper::drawRectangle(point, 2, Qt::green);
    }
}
