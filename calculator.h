#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QtWidgets>
#include "button.h"
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

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
    Button *createButton(const QString &text, const char *member);
    QLineEdit *display;
    static const int NumDigitButtons = 10;
    Button *digitButtons[NumDigitButtons];
};
#endif
