#include "include/abstractcalcu.h"
//#include "include/token.h"
#include <iostream>
#include <string>
#include <QDebug>
#include <cmath>
#include <cstdlib>

#define DEBUG(a) std::cout << __LINE__ << ": " << a << std::endl; std::cout.flush();

AbstractCalcu::AbstractCalcu(QWidget *parent, int minw, int minh, int iconsize, int fontsize) :
    QWidget(parent),
    minwidth(minw),
    minheight(minh),
    iconsize(iconsize),
    fontsize(fontsize)
{
    BuildButtons();
}


AbstractCalcu::~AbstractCalcu()
{
}

void AbstractCalcu::BuildButtons()
{
    display = new QLineEdit("");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(2*minheight);
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
    backspaceButton->setIcon(QIcon(":/new/icon/backspace.png"));
}

void AbstractCalcu::SetCalcuLayout()
{

}

QToolButton *AbstractCalcu::createButton(const QString &text, const char *member)
{
    QToolButton *button = new QToolButton();
    button->setText(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    button->setMinimumWidth(minwidth);
    button->setMinimumHeight(minheight);
    button->setIconSize(QSize(iconsize, iconsize));
    QFont font("Helvetica");
    font.setPointSize(fontsize);
    button->setFont(font);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void AbstractCalcu::digitClicked()
{
    QToolButton* button = qobject_cast<QToolButton*>(sender());
    QString value = button->text();
    std::string str = value.toUtf8().toStdString();

    // to delete the token when meet backspace,
    // add ' ' in front of the tokens

    // number
    DEBUG(dictStr.find(str))
    if(dictStr.find(str) <= dictStr.length()){
        if(numFlag == true){
            numStr += str;
            int pos =output.lastIndexOf(QChar(' '));
            DEBUG(output.right(output.length() - pos).toStdString())
            value = output.right(output.length() - pos) + value;
            output.truncate(pos);
        }
        else{
            numStr = str;
            value = " " + value;
        }
        numFlag = true;
    }
    else{
        if(numFlag == true){
            DEBUG(atof(numStr.c_str()))
            list.getNum(atof(numStr.c_str()));
        }
        numFlag = false;
    }

    // as for sin,cos,exp,tan,log we need '('
    if(str == "sin" ||
            str == "cos" ||
            str == "tan" ||
            str == "ln" ){
        list.getString(str);
        value = " " + value + " (";
    }
    // ^
    else if(str == "^"){
        value = " ^";
        list.getString("^");
    }
    // ^ 2
    else if(str == "x^2"){
        value = " ^ 2";
        list.getString("^");
        list.getNum(2);
    }
    // ^ ( 1 / 2 )
    else if(str == "x^(1/2)"){
        value = " ^ ( 1 / 2 )";
        list.getString("^");
        list.getString("(");
        list.getNum(1);
        list.getString("/");
        list.getNum(2);
        list.getString(")");
    }
    // 1 /
    else if(str == "1/x"){
        value = " 1 /";
        list.getNum(1);
        list.getString("/");
    }
    // 10 ^
    else if(str == "10^x"){
        value = " 10 ^";
        list.getNum(10);
        list.getString("^");
    }
    // e ^
    else if(str == "exp"){
        value = " e ^";
        list.getNum(M_E);
        list.getString("^");
    }
    // pi
    else if(str == "PI"){
        value = " pi";
        list.getNum(M_PI);
    }
    // !
    else if(str == "n!"){
        value = " !";
        list.getString("!");
    }
    // +-()
    else if(str == "+" ||
            str == "-" ||
            str == "(" ||
            str == ")" ){
        value = " " + value;
        list.getString(str);
    }
    // modulo
    else if(str == "mod" ||
            str == "%"){
        value = " %";
        list.getString("%");
    }
    // *
    else if(str == timesButton->text().toStdString()){
        value = " *";
        list.getString("*");
    }
    // /
    else if(str == divisionButton->text().toStdString()){
        value = " /";
        list.getString("/");
    }
    // control
    else if(str == "CE"){
        list.list_.clear();
        output = "";
    }
    // if meets backspace, then delete chars on the right of the last ' '.
    else if(str == "back"){
        int pos =output.lastIndexOf(QChar(' '));
        std::string token = output.right(output.length() - pos - 1).toStdString();
        if(token == "("){
            output.truncate(pos);
            pos =output.lastIndexOf(QChar(' '));
            token = output.right(output.length() - pos - 1).toStdString();
        }
        list.getString("back");
        output.truncate(pos);
    }
    // '=': then we need to add the output to the list and calculate.
    else if(str == "="){
        list.getString("end");
        double result = list.calculate();
        DEBUG("")
        list = token_list::List();
        numFlag = false;
        DEBUG("")
        list.getNum(result);
        DEBUG(result)
        std::string finalResult = std::to_string(result);
        // delete the tailing '0' and '.'
        int posPoint = finalResult.find('.');
        if(posPoint < finalResult.length()){
            int posZero = finalResult.find_last_of('0');
            while(posZero > posPoint && posZero == finalResult.length() - 1){
                finalResult.pop_back();
                posZero = finalResult.find_last_of('0');
            }
            if (posPoint == finalResult.length() - 1)
                finalResult.pop_back();
        }
        output = QString::fromStdString(finalResult);
    }

    if(str != "CE" && str != "back" && str != "="){
        if(output == "0")
            output = value;
        else{
            output.append(value);
        }

    }std::cout << output.toUtf8().toStdString();
    std::cout.flush();

    // at least '0'
    if(output.length() == 0)
        output = "0";
    display->setText(output);

}
