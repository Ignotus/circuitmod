#include <QDebug>
#include <QMoveEvent>
#include <QScrollArea>
#include <ctime>
#include "simulationwidget.h"
#include "typedefs.h"
#include "drawinghelper.h"

SimulationWidget::SimulationWidget(QWidget* parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer), parent)
{
    setAutoBufferSwap(true);
}

void SimulationWidget::addData(int id , bool value)
{
    m_data[id] << value;
    
    const int size = m_data.begin()->size();
    const int count = m_data.size();
    
    const int fwidth = size * CIRCUIT_WIDTH;
    const int fheight = count * CIRCUIT_HEIGHT;
    const int wwidth = width();
    const int wheight = height();
    if (wwidth < fwidth || wheight < fheight)
    {
        const int w = std::max(wwidth, fwidth);
        const int h = std::max(wheight, fheight);
        parentWidget()->setMinimumSize(w, h);
        resize(w, h);
    }
}

void SimulationWidget::clearData()
{
    m_data.clear();
}

void SimulationWidget::initializeGL()
{
    qglClearColor(Qt::white);
}

void SimulationWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    const int wwidth = width();
    const int wheight = height();
    glOrtho(0, wwidth, wheight, 0, 1, 0);
    glEnable(GL_BLEND);
    glEnable(GL_SMOOTH);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (m_data.begin() == m_data.end())
        return;
    
    for (int i = 0, max = m_data.size() - 1; i < max; ++i)
    {
        const int y = (i + 1) * CIRCUIT_HEIGHT;
        
        DrawingHelper::drawLine({0, y}, {wwidth, y});
    }
    
    int i = 0;
    QMapIterator<int, QVector<bool>> it(m_data);
    while (it.hasNext())
    {
        it.next();
        const QVector<bool>& signal = it.value();
        const int y_max = (i + 1) * CIRCUIT_HEIGHT - 5;
        const int y_min = i * CIRCUIT_HEIGHT + 5;
        
        DrawingHelper::drawText({5, y_min + 15}, "E" + QString::number(it.key()), this);
        
        bool prevSignal = false;
        for (int k = 0, max = signal.size(); k != max; ++k)
        {
            const bool currentSignal = signal[k];
            if (currentSignal)
                DrawingHelper::drawLine({k * CIRCUIT_WIDTH, y_max}, {(k + 1) * CIRCUIT_WIDTH, y_max});
            else
                DrawingHelper::drawLine({k * CIRCUIT_WIDTH, y_min}, {(k + 1) * CIRCUIT_WIDTH, y_min});
            
            if (prevSignal != currentSignal)
                DrawingHelper::drawLine({k * CIRCUIT_WIDTH, y_max},
                                        {k * CIRCUIT_WIDTH, y_min});
            
            prevSignal = signal[k];
        }
        ++i;
    }
}

void SimulationWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}