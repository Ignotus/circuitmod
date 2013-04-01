#include <typeinfo>
#include <QFont>
#include <QDebug>
#include <QMouseEvent>
#include "editorview.h"
#include "editormodel.h"
#include "circuits/circuits.h"
#include "views/views.h"

EditorView::EditorView(QWidget *parent)
    : QGLWidget(parent)
    , m_isWidgetPressed(false)
    , m_model(NULL)
    , m_width(width())
    , m_height(height())
{
    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);
    updateGL();
}

void EditorView::setModel(EditorModel *model)
{
    m_model = model;

    if (!m_circuitViews.empty())
        m_circuitViews.clear();

    const EditorModel::CircuitVector& circuits = m_model->circuits();

    for (int i = 0, max = circuits.size(); i != max; ++i)
        m_circuitViews.push_back(constructCircuitView(circuits[0].get()));
}


void EditorView::initializeGL()
{
    qDebug() << Q_FUNC_INFO;
    qglClearColor(Qt::white);
}

ICircuitView* EditorView::constructCircuitView(ICircuit *model)
{
    const std::type_info& info = typeid(*model);
    
    if (info == typeid(And2))
    {
        ICircuitView *view = new And2View(this);
        view->setModel(model);
        view->setBeginPoint(QPoint(100, 100));
        return view;
    }
    
    return NULL;
}

void EditorView::paintGL()
{
    qDebug() << Q_FUNC_INFO;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_width, m_height, 0, 1, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    foreach (ICircuitView *const view, m_circuitViews)
        view->draw();

    swapBuffers();
}

void EditorView::resizeGL(int width, int height)
{
    qDebug() << Q_FUNC_INFO;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)width, (GLint)height);

    m_width = width;
    m_height = height;
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    m_isWidgetPressed = true;
   
    const QPoint& current = e->pos();
    foreach (ICircuitView *const element, m_circuitViews)
    {
        qDebug() << Q_FUNC_INFO << current << " " << element->border();
        if (element->border().containsPoint(current, Qt::OddEvenFill))
        {
            element->select();
            element->setMousePosition(current - element->beginPoint());
        }
        else
            element->unselect();
    }
    
    
    updateGL();
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    m_isWidgetPressed = false;

}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    if (!m_isWidgetPressed)
        return;
    
    const QPoint& current = e->pos();
    foreach (ICircuitView *const element, m_circuitViews)
    {
        if (element->isSelected())
            element->setBeginPoint(current - element->mousePosition());
    } 
    
    updateGL();
}
