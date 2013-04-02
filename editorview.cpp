#include <typeinfo>
#include <QFont>
#include <QDebug>
#include <QMouseEvent>
#include <QAction>
#include "editorview.h"
#include "editormodel.h"
#include "drawinghelper.h"
#include "elementadder.h"
#include "icircuitview.h"

EditorView::EditorView(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer), parent)
    , m_isWidgetPressed(false)
    , m_model(NULL)
    , m_width(width())
    , m_height(height())
{
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
    
    glDepthFunc(GL_LEQUAL);
}

void EditorView::setModel(EditorModel *model)
{
    m_model = model;

    if (!m_circuitViews.empty())
        m_circuitViews.clear();
    
    m_adder.reset(new ElementAdder(model, this));

    const EditorModel::CircuitVector& circuits = m_model->circuits();

    for (int i = 0, max = circuits.size(); i != max; ++i)
        m_circuitViews << m_adder->constructCircuitView(circuits[i].get());
}


void EditorView::initializeGL()
{
    qglClearColor(Qt::white);
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
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    m_width = width;
    m_height = height;
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton)
        return;
    
    setFocus();
    m_isWidgetPressed = true;
   
    if (m_adder->hasCurrentElement())
        return;
    
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

void EditorView::moveElements(const QPoint& pos)
{
    foreach (ICircuitView *const element, m_circuitViews)
    {
        if (element->isSelected())
        {
            element->setBeginPoint(pos - element->mousePosition());
            break;
        }
    }
}

void EditorView::addElement(const QPoint& pos)
{
    ICircuitView *v = m_adder->constructCurrentView(pos);
    m_circuitViews.push_back(v);
    v->select();
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    m_isWidgetPressed = false;

    if (m_adder->hasCurrentElement())
    {
        addElement(e->pos());
        
        if (e->modifiers() != Qt::SHIFT)
        {
            emit uncheckActions();
            m_adder->clear();
        }
    }
    
    updateGL();
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    const QPoint& current = e->pos();
    if (e->modifiers() == Qt::SHIFT)
        return;
    
    if (m_isWidgetPressed)
        moveElements(current);
    
    updateGL();
}

void EditorView::deleteSelectedElements()
{
    QVector<ICircuitView*>::iterator it = m_circuitViews.begin();
   
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
}

void EditorView::keyPressEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Delete)
        return;
    
    deleteSelectedElements();
    
    updateGL();
}

void EditorView::onElementAdded(bool checked)
{
    QAction *action = qobject_cast<QAction*>(sender());
    if (action == NULL)
        return;
    
    const QString& type = action->property("type").toString();
    if (!checked)
    {
        if (m_adder && type == m_adder->currentName())
            m_adder->clear();
        return;
    }
    
    m_adder->setCurrentElement(type);
}