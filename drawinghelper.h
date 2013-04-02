#pragma once
#include <QColor>

class QPolygon;
class QPoint;
class EditorView;
struct DrawingHelper
{
    static void drawPolygon(const QPolygon& poly, const QColor& color = Qt::black);
    static void drawRectangle(const QPoint& center, int padding, const QColor& color = Qt::black);
    static void drawInputWire(const QPoint& end, const QColor& color = Qt::black);
    static void drawOutputWire(const QPoint& begin, const QColor& color = Qt::black);
    static void drawLine(const QPoint& first, const QPoint& second, const QColor& color = Qt::black);
    
    static void drawPolygonBorder(const QPolygon& poly, const QColor& color = Qt::black);
    
    static void drawText(const QPoint& begin, const QString& text,
                         EditorView *view, const QColor& color = Qt::black);
};

