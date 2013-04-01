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
    
    EditorView *ev = new EditorView(this);
    setCentralWidget(ev);
    
    m_editorModel.reset(new EditorModel);
    m_editorModel->add(new And2);

    ev->setModel(m_editorModel.get());
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
