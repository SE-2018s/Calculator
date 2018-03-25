#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sci_calcu = new ScientificCalcu();
    setCentralWidget(sci_calcu);
}

MainWindow::~MainWindow()
{
    delete ui;
}
