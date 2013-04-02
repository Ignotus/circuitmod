#include "notview.h"
#include "typedefs.h"
#include "drawinghelper.h"

NotView::NotView(EditorView* parent)
    : ICircuitView(parent)
{

}

void NotView::draw()
{
    drawImpl({CIRCUIT_HEIGHT / 2}, {CIRCUIT_HEIGHT / 2}, "!");
    DrawingHelper::drawCircle(beginPoint() + QPoint(CIRCUIT_WIDTH, CIRCUIT_HEIGHT / 2), 4, Qt::black);
}