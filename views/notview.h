#pragma once
#include "icircuitview.h"

class NotView : public ICircuitView
{
public:
    NotView(EditorView *parent = 0);

    void draw();
};
