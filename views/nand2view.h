#pragma once
#include <icircuitview.h>
class Nand2View : public ICircuitView
{
public:
    Nand2View(EditorView *parent = 0);

    void draw();
};