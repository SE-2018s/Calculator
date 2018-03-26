#ifndef ABSTRACTCALCU_H
#define ABSTRACTCALCU_H

#include <QWidget>
#include <QtWidgets>
#include <QToolButton>
#include <QLineEdit>
#include "token.h"

class AbstractCalcu : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractCalcu(QWidget *parent = 0);
    virtual ~AbstractCalcu();

protected slots:
    void digitClicked();

protected:
    QToolButton *createButton(const QString &text, const char *member);
    virtual void BuildButtons();
    virtual void SetCalcuLayout()=0;
protected:
    static const int NumDigitButtons = 10;

    //common QObjects
    QLineEdit *display;

    QToolButton *digitButtons[NumDigitButtons];
    QToolButton *pointButton;
    QToolButton *changeSignButton;

    QToolButton *divisionButton;
    QToolButton *timesButton;
    QToolButton *minusButton;
    QToolButton *plusButton;
    QToolButton *equalButton;

    QToolButton *clearEntryButton;
    QToolButton *clearButton;
    QToolButton *backspaceButton;

    QString output;

    // zevin's modification.
private:
    token_list::List list;

};

#endif // ABSTRACTCALCU_H
