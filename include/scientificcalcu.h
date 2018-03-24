#ifndef SCIENTIFICCALCU_H
#define SCIENTIFICCALCU_H

#include <QWidget>
#include "abstractcalcu.h"

namespace Ui {
class ScientificCalcu;
}

class ScientificCalcu : public AbstractCalcu
{
    Q_OBJECT

public:
    explicit ScientificCalcu();
    ~ScientificCalcu();

private:
    Ui::ScientificCalcu *ui;

    void BuildButtons() override;
    void SetCalcuLayout() override;

    QToolButton *squareButton;
    QToolButton *powButton;
    QToolButton *sinButton;
    QToolButton *cosButton;
    QToolButton *tanButton;
    QToolButton *squareRootButton;
    QToolButton *tenExpButton;
    QToolButton *logButton;
    QToolButton *expButton;
    QToolButton *modButton;
    QToolButton *upButton;

    QToolButton *piButton;
    QToolButton *factButton;

    QToolButton *lBracketButton;
    QToolButton *rBracketButton;
};

#endif // SCIENTIFICCALCU_H
