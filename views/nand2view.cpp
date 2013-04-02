#include "nand2view.h"
#include "typedefs.h"
#include "drawinghelper.h"

Nand2View::Nand2View(EditorView *parent)
    : ICircuitView(parent)
{
}

void Nand2View::draw()
{
    drawImpl({CIRCUIT_HEIGHT / 4, CIRCUIT_HEIGHT * 3 / 4}, {CIRCUIT_HEIGHT / 2}, "&");
    DrawingHelper::drawCircle(beginPoint() + QPoint(CIRCUIT_WIDTH, CIRCUIT_HEIGHT / 2), 4, Qt::black);
}