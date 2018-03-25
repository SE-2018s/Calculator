#ifndef PROGRAMCALCU_H
#define PROGRAMCALCU_H

#include "abstractcalcu.h"

namespace Ui {
class ProgramCalcu;
}

class ProgramCalcu : public AbstractCalcu
{
    Q_OBJECT

public:
    explicit ProgramCalcu();
    ~ProgramCalcu();

private:
    Ui::ProgramCalcu *ui;

    void BuildButtons() override;
    void SetCalcuLayout() override;

    QToolButton* lshButton;
    QToolButton* rshButton;
    QToolButton* orButton;
    QToolButton* xorButton;
    QToolButton* notButton;
    QToolButton* andButton;
    QToolButton* upButton;
    QToolButton* modButton;
    QToolButton* hexButtons[6];
    QToolButton* lBracketButton;
    QToolButton* rBracketButton;
};

#endif // PROGRAMCALCU_H
