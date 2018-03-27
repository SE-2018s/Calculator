#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scientificcalcu.h"
#include "ordinarycalcu.h"
#include "programcalcu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void SelectCalcu();
    void About();

private:
    Ui::MainWindow *ui;
    ScientificCalcu* sci_calcu;
    OrdinaryCalcu* ordi_calcu;
//    ProgramCalcu* program_calcu;

    QStackedWidget *stacked_calcu;

    QMenu* type_menu;
    QMenu* about_menu;
    QToolBar* type_toolbar;

    QAction* select_ordi;
    QAction* select_sci;
    QAction* select_program;
    QAction* about_act;

private:
    void CreateActions();
    void CreateMenu();
    void CreateToolBar();
};

#endif // MAINWINDOW_H
