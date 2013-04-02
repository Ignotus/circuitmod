#pragma once

class EditorView;
class QPoint;
class WireManager
{
public:
    WireManager(EditorView *view);
    void selectIO(const QPoint& pos);
private:
    EditorView * const m_view;
};
