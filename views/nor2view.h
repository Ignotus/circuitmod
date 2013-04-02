#pragma once
#include "icircuitview.h"

class Nor2View : public ICircuitView
{
public:
    Nor2View(EditorView *parent = 0);

    void draw();
};