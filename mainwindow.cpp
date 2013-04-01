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
    m_editorModel->add(new And2);

    ev->setModel(m_editorModel.get());

    setCentralWidget(ev);
    
    QAction *and2Selector = m_ui->toolBar->addAction(QIcon(), "And2");
    and2Selector->setProperty("type", QString(typeid(And2).name()));
    and2Selector->setCheckable(true);
    
    connect(and2Selector, SIGNAL(triggered(bool)), ev, SLOT(onElementAdded()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
