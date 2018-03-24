#ifndef ORDINARYCALCU_H
#define ORDINARYCALCU_H

#include "abstractcalcu.h"

namespace Ui {
class OrdinaryCalcu;
}

class OrdinaryCalcu : public AbstractCalcu
{
    Q_OBJECT

public:
    explicit OrdinaryCalcu();
    ~OrdinaryCalcu();

private:
    Ui::OrdinaryCalcu *ui;
    void BuildButtons() override;
    void SetCalcuLayout() override;

    QToolButton *percentButton;
    QToolButton *squareRootButton;
    QToolButton *squareButton;
    QToolButton *invButton;
};

#endif // ORDINARYCALCU_H
