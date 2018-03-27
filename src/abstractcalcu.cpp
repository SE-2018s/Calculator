#include "include/abstractcalcu.h"

#include <QDebug>
AbstractCalcu::AbstractCalcu(QWidget *parent) :
    QWidget(parent)
{
    BuildButtons();
}


AbstractCalcu::~AbstractCalcu()
{
}

void AbstractCalcu::BuildButtons()
{
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    //build buttons
    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }
    pointButton = createButton(tr("."), SLOT(digitClicked()));
    divisionButton = createButton(tr("\303\267"), SLOT(digitClicked()));
    timesButton = createButton(tr("\303\227"), SLOT(digitClicked()));
    minusButton = createButton(tr("-"), SLOT(digitClicked()));
    plusButton = createButton(tr("+"), SLOT(digitClicked()));
    equalButton = createButton(tr("="), SLOT(digitClicked()));
    changeSignButton = createButton(tr("\302\261"), SLOT(digitClicked()));

    clearEntryButton = createButton(tr("CE"), SLOT(digitClicked()));
    clearButton = createButton(tr("C"), SLOT(digitClicked()));
    backspaceButton = createButton(tr("back"), SLOT(digitClicked()));
}

void AbstractCalcu::SetCalcuLayout()
{

}

QToolButton *AbstractCalcu::createButton(const QString &text, const char *member)
{
    QToolButton *button = new QToolButton();
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void AbstractCalcu::digitClicked()
{
    QToolButton* button = qobject_cast<QToolButton*>(sender());
    QString value = button->text();
    output.append(value);
    display->setText(output);
}
