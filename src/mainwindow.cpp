#include "./include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sci_calcu = new ScientificCalcu();
    //ordi_calcu = new OrdinaryCalcu();
    //program_calcu = new ProgramCalcu();
    //current_calcu = qobject_cast<AbstractCalcu*>(sci_calcu);
    //setCentralWidget(current_calcu);
    setCentralWidget(sci_calcu);
    CreateActions();
    CreateMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateActions()
{
    select_ordi = new QAction(tr("Ordinary"), this);
    select_ordi->setStatusTip(tr("Choose ordinary calculator"));
    connect(select_ordi, SIGNAL(triggered()), this, SLOT(SelectCalcu()));

    select_sci = new QAction(tr("Scientific"), this);
    select_sci->setStatusTip(tr("Choose scientific calculator"));
    connect(select_sci, SIGNAL(triggered()), this, SLOT(SelectCalcu()));

    select_program = new QAction(tr("Program"), this);
    select_program->setStatusTip(tr("Choose programmer's calculator"));
    connect(select_program, SIGNAL(triggered()), this, SLOT(SelectCalcu()));
}


void MainWindow::CreateMenu()
{
    main_menu = menuBar()->addMenu(tr("&Type"));
    main_menu->addAction(select_ordi);
    main_menu->addAction(select_sci);
    main_menu->addAction(select_program);
}

void MainWindow::SelectCalcu()
{
    QString type = qobject_cast<QAction*>(sender())->text();
    /*
    if (type == QString(tr("Ordinary")))
        setCentralWidget(ordi_calcu);
    else if (type == QString("Scientific"))
        setCentralWidget(sci_calcu);
    else setCentralWidget(program_calcu);
    */
    qDebug() << type;
}
