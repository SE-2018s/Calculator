#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QtWidgets>
#include "button.h"
#include <QLineEdit>
#include <QString>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);


private slots:
    void digitClicked();
    void pointClicked();
    void test();

private:
    QLineEdit *display;
    static const int NumDigitButtons = 10;
    Button *digitButtons[NumDigitButtons];
    QString* output;
};
#endif
