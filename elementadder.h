#pragma once
#include <QString>
class ICircuitView;
class EditorModel;
class ICircuit;
class EditorView;
class QPoint;
class ElementAdder
{
public:
    ElementAdder(EditorModel *em, EditorView *view);
    
    void setCurrentElement(const QString& name);
    void clear();
    
    const QString& currentName() const;
    
    bool hasCurrentElement() const;
    
    ICircuitView* constructCurrentView(const QPoint& begin);
    ICircuitView* constructCircuitView(ICircuit *model);
    
private:
    EditorModel *const m_em;
    QString m_name;
    EditorView *const m_view;
};