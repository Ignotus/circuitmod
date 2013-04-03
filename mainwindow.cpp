#include <QToolBar>
#include <QIcon>
#include <QScrollArea>
#include <QDebug>
#include <QTimer>
#include <QDate>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editorview.h"
#include "editormodel.h"
#include "simulationwidget.h"

#include "circuits/circuits.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_timer(NULL)
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
    m_ui->toolBar->addAction("Stop", this, SLOT(stop()));
    
    m_ui->toolBar->addSeparator();
    
    addActionForCircuit<And2>(ev, "And2");
    addActionForCircuit<NAnd2>(ev, "NAnd2");
    addActionForCircuit<Or2>(ev, "Or2");
    addActionForCircuit<NOr2>(ev, "NOr2");
    addActionForCircuit<Not>(ev, "Not");
    
    addActionForCircuit<Input>(ev, "In");
    addActionForCircuit<Output>(ev, "Out");
   
    m_simuWidget = new SimulationWidget(m_ui->scrollAreaWidgetContents);
    
    m_ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_ui->scrollAreaWidgetContents->resize(m_ui->scrollArea->size().width() , m_ui->scrollArea->size().height());
    m_ui->scrollArea->setWidgetResizable(true);
    m_ui->scrollArea->setWidget(m_ui->scrollAreaWidgetContents);
    m_ui->scrollAreaWidgetContents->adjustSize();
}

void MainWindow::stop()
{
    if (m_timer)
    {
        m_timer->stop();
        m_timer->deleteLater();
        m_timer = NULL;
    }
}

void MainWindow::uncheckToolbar()
{
    foreach(QAction * const selector, m_toolBarActions)
        selector->setChecked(false);
}

void MainWindow::onSignalChanged(int id, bool value)
{
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

void MainWindow::sendSignal()
{
    {
        EditorModel::CircuitCollection& inputs = m_editorModel->inputs();
        QHashIterator<int, std::shared_ptr<ICircuit>> i(inputs);
        
        while (i.hasNext())
        {
            i.next();
            
            
            const bool sig = rand() % 2 == 0 ? true : false;
            qDebug() << Q_FUNC_INFO << "Input" << i.value()->id() << sig;
            m_simuWidget->addData(i.value()->id(), sig);
            qobject_cast<Input*>(i.value().get())->onSignal(sig);
        }
    }
    
    {
        EditorModel::CircuitCollection& outputs = m_editorModel->outputs();
        QHashIterator<int, std::shared_ptr<ICircuit>> i(outputs);
        
        while (i.hasNext())
        {
            i.next();
            
            m_simuWidget->addData(i.value()->id(), i.value()->state("OUT_" + QString::number(i.value()->id())));
            qDebug() << Q_FUNC_INFO << "Output" << QString::number(i.value()->id())
                     << i.value()->state("OUT_" + QString::number(i.value()->id()));
        }
    }
    
    m_simuWidget->updateGL();
}

void MainWindow::simulate()
{
    m_simuWidget->clearData();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sendSignal()));
    m_timer->start(250);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
