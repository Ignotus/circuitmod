#include <QtOpenGL>
#include <QDebug>
#include "and2view.h"
#include "typedefs.h"

And2View::And2View(QWidget *parent)
    : ICircuitView(parent)
{
}

void And2View::draw(const QPoint& begin)
{
    qDebug() << Q_FUNC_INFO;

    glBegin(GL_POLYGON);
        glColor4f(0,1,0, 0.25);
        glVertex2f(begin.x(), begin.y());
        glVertex2f(begin.x() + CIRCUIT_WIDTH, begin.y());
        glVertex2f(begin.x() + CIRCUIT_WIDTH, begin.y() + CIRCUIT_HEIGHT);
        glVertex2f(begin.x(), begin.y() + CIRCUIT_HEIGHT);
    glEnd();
}
