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

private:
    Ui::MainWindow *ui;
    //AbstractCalcu* current_calcu;
    ScientificCalcu* sci_calcu;
    //OrdinaryCalcu* ordi_calcu;
    //ProgramCalcu* program_calcu;
    QMenu* main_menu;
    QMenu* about_menu;

    QAction* select_ordi;
    QAction* select_sci;
    QAction* select_program;

private:
    void CreateActions();
    void CreateMenu();
    void CreateToolBar();

};

#endif // MAINWINDOW_H
