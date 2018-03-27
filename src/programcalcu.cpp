#include "include/programcalcu.h"
#include "ui_programcalcu.h"

ProgramCalcu::ProgramCalcu()
    :AbstractCalcu(nullptr, 20*3, 7*9, 26, 16),
    ui(new Ui::ProgramCalcu)
{
    //8 blocks
    BuildButtons();
    SetCalcuLayout();
}

ProgramCalcu::~ProgramCalcu()
{
    delete ui;
}

void ProgramCalcu::BuildButtons()
{
	lshButton = createButton(tr("lsh"), SLOT(digitClicked()));
	rshButton = createButton(tr("rsh"), SLOT(digitClicked()));
	orButton = createButton(tr("or"), SLOT(digitClicked()));
    xorButton = createButton(tr("xor"), SLOT(digitClicked()));
	notButton = createButton(tr("not"), SLOT(digitClicked()));
	andButton = createButton(tr("and"), SLOT(digitClicked()));
	upButton = createButton(tr("up"), SLOT(digitClicked()));
	modButton = createButton(tr("mod"), SLOT(digitClicked()));
	for(int i = 0; i < 6; i++)
	{
        char name[2] = {char('A'+i), 0};
        hexButtons[i] = createButton(tr(name), SLOT(digitClicked()));
	}
    lBracketButton = createButton(tr("("), SLOT(digitClicked()));
    rBracketButton = createButton(tr(")"), SLOT(digitClicked()));
}

void ProgramCalcu::SetCalcuLayout()
{
	QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(lshButton, 1, 0);
    mainLayout->addWidget(rshButton, 1, 1);
    mainLayout->addWidget(orButton, 1, 2);
    mainLayout->addWidget(xorButton, 1, 3);
    mainLayout->addWidget(notButton, 1, 4);
    mainLayout->addWidget(andButton, 1, 5);
    mainLayout->addWidget(upButton, 2, 0);
    mainLayout->addWidget(modButton, 2, 1);
    mainLayout->addWidget(clearEntryButton, 2, 2);
    mainLayout->addWidget(clearButton, 2, 3);
    mainLayout->addWidget(backspaceButton, 2, 4);
    mainLayout->addWidget(divisionButton, 2, 5);
    mainLayout->addWidget(timesButton, 3, 5);
    mainLayout->addWidget(minusButton, 4, 5);
    mainLayout->addWidget(plusButton, 5, 5);
    mainLayout->addWidget(equalButton, 6, 5);
    mainLayout->addWidget(upButton, 3, 0);
    mainLayout->addWidget(modButton, 3, 1);
    mainLayout->addWidget(clearEntryButton, 3, 2);
    mainLayout->addWidget(clearButton, 3, 3);
    mainLayout->addWidget(backspaceButton, 3, 4);
    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 3;
        int column = ((i - 1) % 3) + 2;
        mainLayout->addWidget(digitButtons[i], row, column);
    }
    mainLayout->addWidget(digitButtons[0], 6, 3);
    mainLayout->addWidget(changeSignButton, 6, 2);
    mainLayout->addWidget(pointButton, 6, 4);
    mainLayout->addWidget(lBracketButton, 6, 0);
    mainLayout->addWidget(rBracketButton, 6, 1);
    for (int i = 0; i < 6; ++i){
        int row = i / 2 + 3;
        int column = i % 2;
        mainLayout->addWidget(hexButtons[i], row, column);
    }
    setLayout(mainLayout);
    setWindowTitle(tr("Programmer Calculator"));
}
