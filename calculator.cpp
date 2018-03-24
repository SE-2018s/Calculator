#include "calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    output = new QString("abc");
    qDebug() << output;
}

void Calculator::digitClicked()
{
}

void Calculator::pointClicked()
{
}

void Calculator::test()
{
}
