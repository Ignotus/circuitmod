#include <QToolBar>
#include <QIcon>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editorview.h"
#include "editormodel.h"

#include "circuits/and2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    
    EditorView *ev = new EditorView;
    
    m_editorModel.reset(new EditorModel);

    ev->setModel(m_editorModel.get());

    setCentralWidget(ev);
    
    addActionForCircuit<And2>(ev, "And2");
}

void MainWindow::uncheckToolbar()
{
    foreach(QAction * const selector, m_toolBarActions)
        selector->setChecked(false);
}

template<class T>
void MainWindow::addActionForCircuit(EditorView *ev, const QString& text, const QIcon& icon)
{
    QAction *selector = m_ui->toolBar->addAction(icon, text);
    selector->setProperty("type", QString(typeid(T).name()));
    selector->setCheckable(true);
    
    connect(selector, SIGNAL(triggered(bool)), ev, SLOT(onElementAdded(bool)));
    connect(selector, SIGNAL(triggered(bool)), this, SLOT(updateToolbar(bool)));
    connect(ev, SIGNAL(uncheckActions()), this, SLOT(uncheckToolbar()));
    m_toolBarActions.push_back(selector);
}

void MainWindow::updateToolbar(bool checked)
{
    if (!checked)
        return;
    
    QAction *action = qobject_cast<QAction*>(sender());
    if (action == NULL)
        return;
    
    foreach(QAction * const selector, m_toolBarActions)
    {
        if (selector != action)
            selector->setChecked(false);
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
