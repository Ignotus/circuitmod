#include <QToolBar>
#include <QIcon>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editorview.h"
#include "editormodel.h"

#include "circuits/circuits.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    
    EditorView *ev = new EditorView;
    
    m_editorModel.reset(new EditorModel);
    
    connect(m_editorModel.get(),
            SIGNAL(signalChanged(int, bool)),
            this,
            SLOT(onSignalChanged(int,bool)));

    ev->setModel(m_editorModel.get());

    setCentralWidget(ev);
    
    m_ui->toolBar->addAction("Simulate", this, SLOT(simulate()));
    
    m_ui->toolBar->addSeparator();
    
    addActionForCircuit<And2>(ev, "And2");
    addActionForCircuit<NAnd2>(ev, "NAnd2");
    addActionForCircuit<Or2>(ev, "Or2");
    addActionForCircuit<NOr2>(ev, "NOr2");
    addActionForCircuit<Not>(ev, "Not");
    
    addActionForCircuit<Input>(ev, "In");
    addActionForCircuit<Output>(ev, "Out");
}

void MainWindow::uncheckToolbar()
{
    foreach(QAction * const selector, m_toolBarActions)
        selector->setChecked(false);
}

void MainWindow::onSignalChanged(int id, bool value)
{
    qDebug() << Q_FUNC_INFO << id << value;
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

void MainWindow::simulate()
{
    EditorModel::CircuitCollection& inputs = m_editorModel->inputs();
    
    for (int k = 0; k < 10; ++k)
    {
        
        QHashIterator<int, std::shared_ptr<ICircuit>> i(inputs);
        
        while (i.hasNext())
        {
            i.next();
            qobject_cast<Input*>(i.value().get())->onSignal(rand() % 2 == 0 ? true : false);
        }
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
