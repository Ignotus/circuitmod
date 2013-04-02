#include <QDebug>
#include "wiremanager.h"
#include "editorview.h"
#include "icircuitview.h"
#include "drawinghelper.h"

WireManager::WireManager(EditorView* view)
    : m_view(view)
{

}

void WireManager::selectIO(const QPoint& pos)
{
    const QVector<ICircuitView*>& circuitViews = m_view->circuitViews();
    foreach (ICircuitView * const view, circuitViews)
    {
        foreach (const QPolygon& poly, view->inputs())
        {
            if (poly.containsPoint(pos, Qt::OddEvenFill))
            {
                DrawingHelper::drawPolygon(poly, Qt::red);
                goto end;
            }
        }
        
        foreach (const QPolygon& poly, view->outputs())
        {
            if (poly.containsPoint(pos, Qt::OddEvenFill))
            {
                DrawingHelper::drawPolygon(poly, Qt::green);
                goto end;
            }
        }
    }
end:
    ;
}