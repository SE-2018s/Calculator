#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProgramCalcu c;
    c.show();
    //Calculator c;
    //c.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
