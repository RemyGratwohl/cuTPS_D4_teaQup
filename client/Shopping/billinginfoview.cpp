#include "billinginfoview.h"
#include "ui_billinginfoview.h"

BillingInfoView::BillingInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillingInfoView)
{
    ui->setupUi(this);
}

BillingInfoView::~BillingInfoView()
{
    delete ui;
}
