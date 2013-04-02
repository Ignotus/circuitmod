#include <typeinfo>
#include <QFont>
#include <QDebug>
#include <QMouseEvent>
#include <QAction>
#include "editorview.h"
#include "editormodel.h"
#include "drawinghelper.h"
#include "icircuitview.h"
#include "icircuit.h"

EditorView::EditorView(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer), parent)
    , m_isWidgetPressed(false)
    , m_model(NULL)
    , m_width(width())
    , m_height(height())
    , m_wireManager(this)
{
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
    
    glDepthFunc(GL_LEQUAL);
}

const EditorView::CircuitViewCollection& EditorView::circuitViews() const
{
    return m_circuitViews;
}

const EditorModel* EditorView::model() const
{
    return m_model;
}

void EditorView::setModel(EditorModel *model)
{
    m_model = model;

    if (!m_circuitViews.empty())
        m_circuitViews.clear();
    
    m_adder.reset(new ElementAdder(model, this));

    const EditorModel::CircuitCollection& circuits = m_model->circuits();

    for (int i = 0, max = circuits.size(); i != max; ++i)
    {
        ICircuit *circuit = circuits[i].get();
        ICircuitView *view = m_adder->constructCircuitView(circuit);
        m_circuitViews[circuit->id()] = view;
    }
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
    glEnable(GL_SMOOTH);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    foreach (ICircuitView *const view, m_circuitViews)
        view->draw();
    
    const QPoint& pos = mapFromGlobal(cursor().pos());
    
    m_wireManager.drawWires();
    m_wireManager.drawTemporaryWire(pos);
    
    if (!m_isWidgetPressed)
    {
        QString name;
        m_wireManager.selectIO(pos, name);
    }
    
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
    if (e->button() == Qt::RightButton)
    {
        m_wireManager.clearPrevPoint();
        
        QString name;
        if (m_wireManager.selectIO(e->pos(), name))
        {
            const QPair<QString, int>& parsed = ICircuit::parseName(name);
            m_wireManager.removeWireTo(parsed.second, name);
        }
        updateGL();
        return;
    }
        
    if (e->button() != Qt::LeftButton)
        return;
    
    setFocus();
    m_isWidgetPressed = true;
   
    QString name;
    if (m_wireManager.selectIO(e->pos(), name))
    {
        const QPair<QString, int>& parsed = ICircuit::parseName(name);
        
        if (m_wireManager.hasPrevPoint())
        {
            m_wireManager.addWireTo(parsed.second, name);
            m_wireManager.clearPrevPoint();
        }
        else
            m_wireManager.setPrevPoint(parsed.second, name);
    }
   
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
    m_circuitViews[v->model()->id()] = v;
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
    EditorModel::CircuitCollection& circuits = m_model->circuits();
    auto cit = circuits.begin();
   
    for (; cit != circuits.end();)
    {
        const int id = (*cit)->id();
        if (m_circuitViews[id]->isSelected())
        {
            foreach (const std::shared_ptr<ICircuit>& circuit, m_model->circuits())
            {
                foreach (const QString& input, m_circuitViews[id]->model()->inputs())
                {
                    circuit->unsubscribe(CircuitSlot(m_circuitViews[id]->model(), input));
                    m_wireManager.removeWireTo(ICircuit::parseName(input).second, input);
                }
            }
            
            cit = circuits.erase(cit);
            m_circuitViews.remove(id);
        }
        else
            ++cit;
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