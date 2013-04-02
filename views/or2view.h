#pragma once
#include "icircuitview.h"

class Or2View : public ICircuitView
{
public:
    Or2View(EditorView *parent = 0);

    void draw();
};