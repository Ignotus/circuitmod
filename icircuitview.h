#pragma once
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
    
    QIcon icon() const;
    
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
    
protected:
    void qglColor(const QColor& c) const;
    
    void drawRectangle(const QPoint& center, int padding) const;
    void drawInputWire(const QPoint& end) const;
    void drawOutputWire(const QPoint& begin) const;
    void drawText(const QPoint& begin, const QString& text) const;
    void drawLine(const QPoint& first, const QPoint& second) const;
    
private:
    ICircuit *m_model;
    EditorView * const m_editor;
    bool m_isSelected;
    
protected:
    QPoint m_begin;
    QPoint m_mousePosition;
};
