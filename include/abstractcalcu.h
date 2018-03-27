#ifndef ABSTRACTCALCU_H
#define ABSTRACTCALCU_H

#include <QWidget>
#include <QtWidgets>
#include <QToolButton>
#include <QLineEdit>


class AbstractCalcu : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractCalcu(QWidget *parent, int, int, int, int);
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
    const int minwidth;
    const int minheight;
    const int fontsize;
    const int iconsize;
    QString output;
};

#endif // ABSTRACTCALCU_H
