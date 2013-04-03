#include <QDebug>
#include <QMoveEvent>
#include "simulationwidget.h"
#include "typedefs.h"
#include "drawinghelper.h"

SimulationWidget::SimulationWidget(QWidget* parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer), parent)
    , m_width(width())
    , m_height(height())
{
}

void SimulationWidget::addData(int id , bool value)
{
    m_data[id] << value;
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
    glOrtho(0, m_width, m_height, 0, 1, 0);
    glEnable(GL_BLEND);
    glEnable(GL_SMOOTH);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (m_data.begin() == m_data.end())
    {
        swapBuffers();
        return;
    }
    
    const int size = m_data.begin()->size();
    const int count = m_data.size();
    
    const int width = size * CIRCUIT_WIDTH;
    const int height = count * CIRCUIT_HEIGHT;
    
    if (m_width < width || m_height < height)
    {
        const int w = std::max(m_width, width);
        const int h = std::max(height, m_height);
        parentWidget()->setMinimumSize(w, h);
        resize(w, h);
        return;
    }
    
    for (int i = 0; i < count - 1; ++i)
    {
        const int y = (i + 1) * CIRCUIT_HEIGHT;
        
        DrawingHelper::drawLine({0, y}, {m_width, y});
    }
    
    int i = 0;
    QMapIterator<int, QVector<bool>> it(m_data);
    while (it.hasNext())
    {
        it.next();
        const QVector<bool>& signal = it.value();
        const int y_max = (i + 1) * CIRCUIT_HEIGHT - 5;
        const int y_min = i * CIRCUIT_HEIGHT + 5;
        
        DrawingHelper::drawText({5, y_min + 15}, "E_" + QString::number(it.key()), this);
        
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
    
    swapBuffers();
}

void SimulationWidget::moveEvent(QMoveEvent *event)
{
    updateGL();
}

void SimulationWidget::resizeGL(int width, int height)
{
    qDebug() << Q_FUNC_INFO;
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    m_height = height;
    m_width = width;
}