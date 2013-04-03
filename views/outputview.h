#pragma once
#include "icircuitview.h"

class OutputView : public ICircuitView
{
public:
    OutputView(EditorView *parent = 0);

    void draw();
};
