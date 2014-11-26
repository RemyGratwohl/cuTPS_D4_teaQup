#ifndef BILLINGINFOVIEW_H
#define BILLINGINFOVIEW_H

#include <QWidget>

namespace Ui {
class BillingInfoView;
}

class BillingInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit BillingInfoView(QWidget *parent = 0);
    ~BillingInfoView();

private:
    Ui::BillingInfoView *ui;
};

#endif // BILLINGINFOVIEW_H
