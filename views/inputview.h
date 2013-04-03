#pragma once
#include "icircuitview.h"

class InputView : public ICircuitView
{
public:
    InputView(EditorView *parent = 0);

    void draw();
};
