#pragma once
#include <memory>
#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class EditorModel;
class EditorView;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
   
private:
    template<class T>
    void addActionForCircuit(EditorView *ev, const QString& text, const QIcon& icon = QIcon());
    
private slots:
    void updateToolbar(bool);
    void uncheckToolbar();
    
private:
    Ui::MainWindow *m_ui;
    std::unique_ptr<EditorModel> m_editorModel;
    
    std::vector<QAction*> m_toolBarActions;
};
