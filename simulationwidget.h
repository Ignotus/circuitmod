#pragma once
#include <QGLWidget>

class SimulationWidget : public QGLWidget
{
public:
    SimulationWidget(QWidget *parent = 0);
    void addData(int id , bool value);
    void clearData();
    
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    
protected:
    void moveEvent(QMoveEvent *event);
    
private:
    int m_width;
    int m_height;
    
    QMap<int, QVector<bool>> m_data;
};
