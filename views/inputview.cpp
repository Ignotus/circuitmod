#include "inputview.h"
#include "typedefs.h"

InputView::InputView(EditorView *parent)
    : ICircuitView(parent)
{
}

void InputView::draw()
{
    drawImpl({}, {CIRCUIT_HEIGHT / 2}, "IN");
}