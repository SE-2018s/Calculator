#include "include/scientificcalcu.h"
#include "ui_scientificcalcu.h"
#include <QDebug>

ScientificCalcu::ScientificCalcu()
    : AbstractCalcu(nullptr, 24*3, 7*8, 20, 16),
       ui(new Ui::ScientificCalcu)
{
    //9 blocks
    BuildButtons();
    SetCalcuLayout();
}

ScientificCalcu::~ScientificCalcu()
{
    delete ui;
}

void ScientificCalcu::BuildButtons()
{
    squareButton = createButton(tr("x^2"), SLOT(digitClicked()));
    squareButton->setIcon(QIcon("icon/square.png"));
    powButton = createButton(tr("^"), SLOT(digitClicked()));
    sinButton = createButton(tr("sin"), SLOT(digitClicked()));
    cosButton = createButton(tr("cos"), SLOT(digitClicked()));
    tanButton = createButton(tr("tan"), SLOT(digitClicked()));
    squareRootButton = createButton(tr("x^(1/2)"),SLOT(digitClicked()));
    squareRootButton->setIcon(QIcon("icon/sroot.png"));
    tenExpButton = createButton(tr("10^x"), SLOT(digitClicked()));
    tenExpButton->setIcon(QIcon("icon/tenpow.png"));
    logButton = createButton(tr("log"), SLOT(digitClicked()));
    expButton = createButton(tr("exp"), SLOT(digitClicked()));
    modButton = createButton(tr("mod"), SLOT(digitClicked()));
    eButton = createButton(tr("e"), SLOT(digitClicked()));


    piButton = createButton(tr("PI"), SLOT(digitClicked()));
    factButton = createButton(tr("n!"), SLOT(digitClicked()));

    lBracketButton = createButton(tr("("), SLOT(digitClicked()));
    rBracketButton = createButton(tr(")"), SLOT(digitClicked()));
}

void ScientificCalcu::SetCalcuLayout()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
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
    mainLayout->addWidget(eButton, 3, 0);
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
        mainLayout->addWidget(digitButtons[i], row, column);
    }
    mainLayout->addWidget(digitButtons[0], 7, 2);
    mainLayout->addWidget(pointButton, 7, 3);

    setLayout(mainLayout);
    setWindowTitle(tr("Scientific Calculator"));
}
