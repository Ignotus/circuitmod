#pragma once
#include <memory>
#include <QGLWidget>
#include <QHash>
#include "wiremanager.h"
#include "elementadder.h"

class ICircuit;
class EditorModel;
class ICircuitView;
class ElementAdder;
class EditorView : public QGLWidget
{
    Q_OBJECT
public:
    typedef QHash<int, ICircuitView*> CircuitViewCollection;
public:
    EditorView(QWidget *parent = 0);
    
    void setModel(EditorModel *model);

    const CircuitViewCollection& circuitViews() const;
    
    const EditorModel* model() const;
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    void deleteSelectedElements();
    void moveElements(const QPoint& pos);
    void addElement(const QPoint& pos);
    
public slots:
    void onElementAdded(bool);
    
private:
    bool m_isWidgetPressed;
    EditorModel *m_model;
    CircuitViewCollection m_circuitViews;

    std::unique_ptr<ElementAdder> m_adder;
    WireManager m_wireManager;
signals:
    void uncheckActions();
};

