#include "or2view.h"
#include "typedefs.h"

Or2View::Or2View(EditorView* parent)
    : ICircuitView(parent)
{
}

void Or2View::draw()
{
    drawImpl({CIRCUIT_HEIGHT / 4, CIRCUIT_HEIGHT * 3 / 4}, {CIRCUIT_HEIGHT / 2}, "1");
}