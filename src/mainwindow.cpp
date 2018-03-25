#include "./include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sci_calcu = new ScientificCalcu();
    ordi_calcu = new OrdinaryCalcu();
    program_calcu = new ProgramCalcu();

    stacked_calcu = new QStackedWidget;
    stacked_calcu->addWidget(ordi_calcu);
    stacked_calcu->addWidget(sci_calcu);
    stacked_calcu->addWidget(program_calcu);
    setCentralWidget(stacked_calcu);
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

    about_act = new QAction(tr("About"), this);
    about_act->setStatusTip(tr("About this calculator"));
    connect(about_act, SIGNAL(triggered(bool)), this, SLOT(About()));
}

void MainWindow::CreateMenu()
{
    type_menu = menuBar()->addMenu(tr("&Type"));
    type_menu->addAction(select_ordi);
    type_menu->addAction(select_sci);
    type_menu->addAction(select_program);
    about_menu = menuBar()->addMenu(tr("&About"));
    about_menu->addAction(about_act);
}

void MainWindow::CreateToolBar()
{
    type_toolbar = addToolBar(tr("&Type"));
    type_toolbar->addAction(select_ordi);
    type_toolbar->addAction(select_sci);
    type_toolbar->addAction(select_program);
    type_toolbar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBar(Qt::TopToolBarArea, type_toolbar);
}

void MainWindow::SelectCalcu()
{
    QString type = qobject_cast<QAction*>(sender())->text();
    if (type == QString(tr("Ordinary")))
        stacked_calcu->setCurrentIndex(0);
    else if(type == QString("Scientific"))
        stacked_calcu->setCurrentIndex(1);
    else stacked_calcu->setCurrentIndex(2);
}

void MainWindow::About()
{
    QMessageBox::about(this, tr("Mini Draw"),
                       tr("This is the calculator designed by USTC Invincible Team"));
}
