#include "nor2view.h"
#include "typedefs.h"
#include "drawinghelper.h"

Nor2View::Nor2View(EditorView* parent)
    : ICircuitView(parent)
{

}

void Nor2View::draw()
{
    drawImpl({CIRCUIT_HEIGHT / 4, CIRCUIT_HEIGHT * 3 / 4}, {CIRCUIT_HEIGHT / 2}, "1");
    DrawingHelper::drawCircle(beginPoint() + QPoint(CIRCUIT_WIDTH, CIRCUIT_HEIGHT / 2), 4, Qt::black);
}
