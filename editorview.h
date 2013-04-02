#pragma once
#include <memory>
#include <QGLWidget>

class ICircuit;
class EditorModel;
class ICircuitView;
class ElementAdder;
class EditorView : public QGLWidget
{
    Q_OBJECT
public:
    EditorView(QWidget *parent = 0);
    
    void setModel(EditorModel *model);
    
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
    QVector<ICircuitView*> m_circuitViews;

    int m_width;
    int m_height;
    
    std::shared_ptr<ElementAdder> m_adder;
signals:
    void uncheckActions();
};

