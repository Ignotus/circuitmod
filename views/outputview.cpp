#include "outputview.h"
#include "typedefs.h"

OutputView::OutputView(EditorView* parent)
    : ICircuitView(parent)
{
}

void OutputView::draw()
{
    drawImpl({CIRCUIT_HEIGHT / 2}, {}, "OUT");
}
