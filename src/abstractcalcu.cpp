#include "include/abstractcalcu.h"
//#include "include/token.h"
#include <iostream>
#include <string>
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
    std::string str = value.toUtf8().toStdString();

    // as for sin,cos,exp,tan,log we need '('
    if(str == "sin" ||
            str == "cos" ||
            str == "tan" ||
            str == "log" ||
            str == "exp" ){
        str += "(";
        value += "(";
    }
    // if meets backspace, then delete chars on the right of the last ' '.
    else if(str == "back"){
        int pos =output.lastIndexOf(QChar(' '));
        output.truncate(pos);
    }
    // '=': then we need to add the output to the list and calculate.
    else if(str == "="){
        std::string expr = output.toUtf8().toStdString();
        expr += " end";
        list.getString("");
        std::cerr << "herererere" ;
        double result = list.calculate();
        std::cerr << result ;
    }
//    else if(str == )

    // to delete the token when meet backspace,
    // add ' ' in front of the tokens
    if (str != "back" && str != "=") {
        str = " " + str;
        value = " " + value;
    }

    std::cout << str << std::endl;
    std::cout << output.toUtf8().toStdString();
    std::cout.flush();
    if(str != "back" && str != "=")
        output.append(value);

    // at least '0'
    if(output.length() == 0)
        output = "0";
    display->setText(output);

}
