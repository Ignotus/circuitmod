#pragma once
#include <QWidget>
#include <qicon.h>

class ICircuit;

class ICircuitView : public QWidget
{
    Q_OBJECT
public:
    ICircuitView(QWidget *parent = 0);
    void setModel(ICircuit *model);
    
    QIcon icon() const;
    
    virtual void draw(const QPoint& begin) = 0;
private:
    ICircuit *m_model;
};
