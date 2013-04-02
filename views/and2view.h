#pragma once
#include "icircuitview.h"

class And2View : public ICircuitView
{
public:
    And2View(EditorView *parent = 0);

    void draw();
};
