#include <typeinfo>
#include <QFont>
#include <QMouseEvent>
#include "editorview.h"
#include "editormodel.h"
#include "circuits/circuits.h"
#include "views/views.h"

EditorView::EditorView(QWidget *parent)
    : QGLWidget(parent)
    , m_isWidgetPressed(false)
    , m_model(NULL)
{
    
}

void EditorView::setModel(EditorModel *model)
{
    m_model = model;

    if (!m_circuitViews.empty())
        m_circuitViews.clear();

    const EditorModel::CircuitVector& circuits = m_model->circuits();

    for (int i = 0, max = circuits.size(); i != max; ++i)
    {
        m_circuitViews.push_back(constructCircuitView(circuits[0].get()));
    }
}


void EditorView::initializeGL()
{
    qglClearColor(Qt::white);
}

ICircuitView* EditorView::constructCircuitView(ICircuit *model)
{
    const std::type_info& info = typeid(*model);
    
    if (info == typeid(And2))
    {
        ICircuitView *view = new And2View(this);
        view->setModel(model);
        return view;
    }
    
    return NULL;
}

void EditorView::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    foreach (ICircuitView *const view, m_circuitViews)
    {
        view->draw(QPoint(10, 10));
    }
}

void EditorView::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    m_isWidgetPressed = true;
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    if (!m_isWidgetPressed)
        return;
    
    
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    m_isWidgetPressed = false;
}
