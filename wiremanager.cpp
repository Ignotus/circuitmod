#include <QDebug>
#include "wiremanager.h"
#include "editorview.h"
#include "icircuitview.h"
#include "drawinghelper.h"
#include "editormodel.h"
#include "icircuit.h"

WireManager::WireManager(EditorView* view)
    : m_view(view)
{
    clearPrevPoint();
}

void WireManager::setPrevPoint(int elementID, const QString& ioname)
{
    m_prevElementID = elementID;
    m_prevIOName = ioname;
}

void WireManager::clearPrevPoint()
{
    m_prevElementID = -1;
    m_prevIOName.clear();
}

bool WireManager::hasPrevPoint() const
{
    return m_prevElementID > -1;
}

void WireManager::selectPrevPoint() const
{
    if (hasPrevPoint())
        select(m_prevElementID, m_prevIOName);
}

void WireManager::drawTemporaryWire(const QPoint& pos) const
{
    if (hasPrevPoint())
        DrawingHelper::drawWire(select(m_prevElementID, m_prevIOName), pos);
}

void WireManager::drawWires() const
{
    QHashIterator<QPair<int, QString>, QPair<int, QString>> i(m_wires);
    
    while (i.hasNext())
    {
        i.next();
        
        const QPair<int, QString>& first = i.key();
        const QPair<int, QString>& second = i.value();
        
        ICircuitView * const view1 = m_view->circuitViews()[first.first];
        ICircuitView * const view2 = m_view->circuitViews()[second.first];
        
        const QPoint& secondPoint = view1->inputs()[first.second].first() + QPoint(4, 4);
        const QPoint& firstPoint = view2->outputs()[second.second].first() + QPoint(4, 4);
        
        DrawingHelper::drawWire(firstPoint, secondPoint);
    }
}

void WireManager::removeWireTo(int elementID, const QString& ioname)
{
    m_wires.remove(qMakePair(elementID, ioname));
}

void WireManager::addWireTo(int elementID, const QString& ioname)
{
    if (!hasPrevPoint())
        return;
    
    ICircuitView * const view1 = m_view->circuitViews()[m_prevElementID];
    ICircuitView * const view2 = m_view->circuitViews()[elementID];
    const QPair<bool, IOType>& res1 = view1->model()->find(m_prevIOName);
    const QPair<bool, IOType>& res2 = view2->model()->find(ioname);
    
    if (!res1.first || !res2.first || res1.second == res2.second)
        return;
    
    if (res1.second == INPUT)
    {
        m_wires[qMakePair(m_prevElementID, m_prevIOName)] = qMakePair(elementID, ioname);
        view1->model()->subscribe(m_prevIOName, CircuitSlot(view2->model(), ioname));
    }
    else
    {
        m_wires[qMakePair(elementID, ioname)] = qMakePair(m_prevElementID, m_prevIOName);
        view2->model()->subscribe(ioname, CircuitSlot(view1->model(), m_prevIOName));
    }
}

QPoint WireManager::select(int elementID, const QString& ioname) const
{
    ICircuitView * const view = m_view->circuitViews()[elementID];
    QHash<QString, QPolygon>::const_iterator it = view->inputs().find(ioname);
    if (it != view->inputs().end())
    {
        DrawingHelper::drawPolygon(*it, Qt::red);
        return it->first() + QPoint(4, 4);
    }
    
    it = view->outputs().find(ioname);
    if (it != view->outputs().end())
    {
        DrawingHelper::drawPolygon(*it, Qt::green);
        return it->first() + QPoint(4, 4);
    }
    
    return QPoint();
}

QString WireManager::findIO(const QHash<QString, QPolygon>& data, const QPoint& pos, const QColor& color)
{
    QHashIterator<QString, QPolygon> i(data);
    while (i.hasNext())
    {
        i.next();
        const QPolygon& poly = i.value();
        if (poly.containsPoint(pos, Qt::OddEvenFill))
        {
            DrawingHelper::drawPolygon(poly, color);
            return i.key();
        }
    }
    
    return QString();
}

bool WireManager::selectIO(const QPoint& pos, QString& name)
{
    const EditorView::CircuitViewCollection& circuitViews = m_view->circuitViews();
    foreach (ICircuitView * const view, circuitViews)
    {
        const QString& res1 = findIO(view->inputs(), pos, Qt::red);
        if (!res1.isEmpty())
        {
            name = res1;
            return true;
        }
        
        const QString& res2 = findIO(view->outputs(), pos, Qt::green);
        
        if (!res2.isEmpty())
        {
            name = res2;
            return true;
        }
    }
    
    return false;
}