#include "billinginfoview.h"
#include "ui_billinginfoview.h"

BillingInfoView::BillingInfoView(ShoppingCartControl *control, QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::BillingInfoView)
{
    ui->setupUi(this);
}

BillingInfoView::~BillingInfoView()
{
    delete ui;
}
