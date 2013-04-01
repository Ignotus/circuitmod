#include <typeinfo>
#include <QFont>
#include <QDebug>
#include <QMouseEvent>
#include <QAction>
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
    , m_selectedCircuit(NULL)
{
    setFormat(QGLFormat(QGL::DoubleBuffer));
    setFocusPolicy(Qt::ClickFocus);
    
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)width, (GLint)height);

    m_width = width;
    m_height = height;
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    setFocus();
    m_isWidgetPressed = true;
   
    const QPoint& current = e->pos();
    
    foreach (ICircuitView *const element, m_circuitViews)
    {
        if (element->border().containsPoint(current, Qt::OddEvenFill))
        {
            element->select();
            element->setMousePosition(current - element->beginPoint());
        }
        else if (e->modifiers() != Qt::SHIFT)
            element->unselect();
    }
    
    updateGL();
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    m_isWidgetPressed = false;

    if (m_selectedCircuit != NULL)
    {
        
        ICircuit *c = EditorModel::construct(m_selectedCircuit->property("type").toString());
        
        m_model->add(c);
        ICircuitView *v = constructCircuitView(c);
        v->setBeginPoint(e->pos());
        m_circuitViews.push_back(v);
        v->select();
        
        if (e->modifiers() != Qt::SHIFT)
        {
            m_selectedCircuit->setChecked(false);
            m_selectedCircuit = NULL;
        }
    }
    
    updateGL();
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    if (!m_isWidgetPressed || e->modifiers() == Qt::SHIFT)
        return;
    
    const QPoint& current = e->pos();
    foreach (ICircuitView *const element, m_circuitViews)
    {
        if (element->isSelected())
            element->setBeginPoint(current - element->mousePosition());
    } 
    
    updateGL();
}

void EditorView::keyPressEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Delete)
        return;
    
    std::vector<ICircuitView*>::iterator it = m_circuitViews.begin();
   
    EditorModel::CircuitVector& circuits = m_model->circuits();
    EditorModel::CircuitVector::iterator cit = circuits.begin();
    
    for (; cit != circuits.end();)
    {
        if ((*it)->isSelected())
        {
            it = m_circuitViews.erase(it);
            cit = m_model->remove(cit);
            
        }
        else
        {
            ++cit;
            ++it;
        }
    }
    
    updateGL();
}

void EditorView::onElementAdded()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if (action == NULL)
        return;
    
    const QString& type = action->property("type").toString();
    if (!action->isChecked())
    {
        if (m_selectedCircuit != NULL && type == m_selectedCircuit->property("type").toString())
            m_selectedCircuit = NULL;
        return;
    }
    
    m_selectedCircuit = action;
}
