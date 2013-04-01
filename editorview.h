#pragma once

#include <QGLWidget>

class ICircuit;
class EditorModel;
class ICircuitView;
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
    ICircuitView* constructCircuitView(ICircuit *model);
    
public slots:
    void onElementAdded();
    
private:
    bool m_isWidgetPressed;
    EditorModel *m_model;
    std::vector<ICircuitView*> m_circuitViews;

    int m_width;
    int m_height;
    
    QAction *m_selectedCircuit;
};

