#include "include/ordinarycalcu.h"
#include "ui_ordinarycalcu.h"

OrdinaryCalcu::OrdinaryCalcu() :
    AbstractCalcu(nullptr, 30*3, 7*9, 30, 18),
    ui(new Ui::OrdinaryCalcu)
{
    //8 blocks
    BuildButtons();
    SetCalcuLayout();
}

OrdinaryCalcu::~OrdinaryCalcu()
{
    delete ui;
}

void OrdinaryCalcu::BuildButtons()
{
    percentButton = createButton(tr("%"), SLOT(digitClicked()));
    squareRootButton = createButton(tr("x^(1/2)"), SLOT(digitClicked()));
    squareRootButton->setIcon(QIcon(":new/sroot"));
    squareButton = createButton(tr("x^2"), SLOT(digitClicked()));
    squareButton->setIcon(QIcon(":new/square"));
    invButton = createButton(tr("1/x"), SLOT(digitClicked()));
    invButton->setIcon(QIcon(":new/inv"));
}

void OrdinaryCalcu::SetCalcuLayout()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(display, 0, 0, 1, 4);
    mainLayout->addWidget(percentButton, 1, 0);
    mainLayout->addWidget(squareRootButton, 1, 1);
    mainLayout->addWidget(squareButton, 1, 2);
    mainLayout->addWidget(invButton, 1, 3);
    mainLayout->addWidget(clearEntryButton, 2, 0);
    mainLayout->addWidget(clearButton, 2, 1);
    mainLayout->addWidget(backspaceButton, 2, 2);
    mainLayout->addWidget(divisionButton, 2, 3);
    mainLayout->addWidget(timesButton, 3, 3);
    mainLayout->addWidget(minusButton, 4, 3);
    mainLayout->addWidget(plusButton, 5, 3);
    mainLayout->addWidget(equalButton, 6, 3);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 3;
        int column = ((i - 1) % 3) + 0;
        mainLayout->addWidget(digitButtons[i], row, column);
    }
    mainLayout->addWidget(digitButtons[0], 6, 1);
    mainLayout->addWidget(pointButton, 6, 2);
    mainLayout->addWidget(changeSignButton, 6, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Ordinary Calculator"));
}
