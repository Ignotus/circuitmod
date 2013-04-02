#pragma once
#include <QHash>
#include <QObject>
#include <QIcon>

class ICircuit;
class EditorView;
class ICircuitView : public QObject
{
    Q_OBJECT
public:
    ICircuitView(EditorView *parent = 0);
    void setModel(ICircuit *model);
    
    ICircuit* model() const;
    
    void setBeginPoint(const QPoint& begin);
    void setMousePosition(const QPoint& pos);
   
    const QPoint& beginPoint() const;
    const QPoint& mousePosition() const;
    virtual void draw();
    
    virtual QPolygon border() const;
    virtual void drawBorder() = 0;
    
    void select();
    bool isSelected() const;
    void unselect();
    
    const QHash<QString, QPolygon>& inputs() const;
    const QHash<QString, QPolygon>& outputs() const;
protected:
    EditorView* editor() const;
    
private:
    ICircuit *m_model;
    EditorView * const m_editor;
    bool m_isSelected;

    QPoint m_begin;
    QPoint m_mousePosition;
    
    QHash<QString, QPolygon> m_inputs;
    QHash<QString, QPolygon> m_outputs;
};
