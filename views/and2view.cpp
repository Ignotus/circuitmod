#include "and2view.h"
#include "typedefs.h"

And2View::And2View(EditorView *parent)
    : ICircuitView(parent)
{
}

void And2View::draw()
{
    drawImpl({CIRCUIT_HEIGHT / 4, CIRCUIT_HEIGHT * 3 / 4}, {CIRCUIT_HEIGHT / 2}, "&");
}
