#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(test()));
    }
    Button *pointButton = createButton(tr("sdf"), SLOT(test()));

    Button *squareButton = createButton(tr("x^2"), SLOT(test()));

    Button *powButton = createButton(tr("x^y"), SLOT(test()));
    Button *sinButton = createButton(tr("sin"), SLOT(test()));
    Button *cosButton = createButton(tr("cos"), SLOT(test()));
    Button *tanButton = createButton(tr("tan"), SLOT(test()));
    Button *squareRootButton = createButton(tr("x^(1/2)"),SLOT(test()));
    Button *tenExpButton = createButton(tr("10^x"), SLOT(test()));
    Button *logButton = createButton(tr("log"), SLOT(test()));
    Button *expButton = createButton(tr("exp"), SLOT(test()));
    Button *modButton = createButton(tr("mod"), SLOT(test()));
    Button *upButton = createButton(tr("up"), SLOT(test()));
    Button *clearEntryButton = createButton(tr("CE"), SLOT(test()));
    Button *clearButton = createButton(tr("C"), SLOT(test()));
    Button *backspaceButton = createButton(tr("back"), SLOT(test()));
    //operator 1

    Button *divisionButton = createButton(tr("\303\267"), SLOT(test()));
    Button *timesButton = createButton(tr("\303\227"), SLOT(test()));
    Button *minusButton = createButton(tr("-"), SLOT(test()));
    Button *plusButton = createButton(tr("+"), SLOT(test()));
    Button *equalButton = createButton(tr("="), SLOT(test()));
    //operator 2
    Button *piButton = createButton(tr("PI"), SLOT(test()));
    Button *factButton = createButton(tr("n!"), SLOT(test()));
    Button *changeSignButton = createButton(tr("\302\261"), SLOT(test()));
    Button *lBracketButton = createButton(tr("("), SLOT(test()));
    Button *rBracketButton = createButton(tr(")"), SLOT(test()));


    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 5);
    mainLayout->addWidget(squareButton, 1, 0);
    mainLayout->addWidget(powButton, 1, 1);
    mainLayout->addWidget(sinButton, 1, 2);
    mainLayout->addWidget(cosButton, 1, 3);
    mainLayout->addWidget(tanButton, 1, 4);
    mainLayout->addWidget(squareRootButton, 2, 0);
    mainLayout->addWidget(tenExpButton, 2, 1);
    mainLayout->addWidget(logButton, 2, 2);
    mainLayout->addWidget(expButton, 2, 3);
    mainLayout->addWidget(modButton, 2, 4);
    mainLayout->addWidget(upButton, 3, 0);
    mainLayout->addWidget(clearEntryButton, 3, 1);
    mainLayout->addWidget(clearButton, 3, 2);
    mainLayout->addWidget(backspaceButton, 3, 3);

    mainLayout->addWidget(divisionButton, 3, 4);
    mainLayout->addWidget(timesButton, 4, 4);
    mainLayout->addWidget(minusButton, 5, 4);
    mainLayout->addWidget(plusButton, 6, 4);
    mainLayout->addWidget(equalButton, 7, 4);

    mainLayout->addWidget(piButton, 4, 0);
    mainLayout->addWidget(factButton, 5, 0);
    mainLayout->addWidget(changeSignButton, 6, 0);
    mainLayout->addWidget(lBracketButton, 7, 0);
    mainLayout->addWidget(rBracketButton, 7, 1);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 4;
        int column = ((i - 1) % 3) + 1;
        qDebug() << row << "," << column;
        mainLayout->addWidget(digitButtons[i], row, column);
    }
    mainLayout->addWidget(digitButtons[0], 7, 2);

    mainLayout->addWidget(pointButton, 7, 3);

    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}

void Calculator::digitClicked()
{
}


Button *Calculator::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void Calculator::pointClicked()
{

}

void Calculator::test()
{

}
