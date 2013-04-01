#pragma once
#include "icircuitview.h"

class And2View : public ICircuitView
{
public:
    And2View(QWidget *parent = 0);

    void draw(const QPoint& begin);
};
