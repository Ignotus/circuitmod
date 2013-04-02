#pragma once
#include <QString>
#include <QPair>
#include <QPolygon>

class EditorView;
class QPoint;
template<class A, class B>
class QHash;
class QColor;
class WireManager
{
public:
    WireManager(EditorView *view);
    bool selectIO(const QPoint& pos, QString& name);
    
    void setPrevPoint(int elementID, const QString& ioname);
    void clearPrevPoint();
    void selectPrevPoint() const;
    
    bool hasPrevPoint() const;
    
    void drawTemporaryWire(const QPoint& pos) const;
    
    void removeWireTo(int elementID, const QString& ioname);
    void addWireTo(int elementID, const QString& ioname);
    
    void drawWires() const;
private:
    QPoint select(int elementID, const QString& ioname) const;
    QString findIO(const QHash<QString, QPolygon>& data, const QPoint& pos, const QColor& color);
private:
    EditorView * const m_view;
    
    int m_prevElementID;
    QString m_prevIOName;
    
    QHash<QPair<int, QString>, QPair<int, QString>> m_wires;
};
