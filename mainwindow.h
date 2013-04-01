#pragma once
#include <memory>
#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class EditorModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *m_ui;
    std::unique_ptr<EditorModel> m_editorModel;
};
