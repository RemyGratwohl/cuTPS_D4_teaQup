#include "billinginfoview.h"
#include "ui_billinginfoview.h"
#include "shoppingcartcontrol.h"

BillingInfoView::BillingInfoView(ShoppingCartControl *control, QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::BillingInfoView)
{
    ui->setupUi(this);
    ui->addressLineEdit->setPlaceholderText("Street address, P.O box, company name, c/o");
    ui->insitutionLineEdit->setPlaceholderText("Payment Method (Bank Name, Paypal, Google Wallet, etc.)");
}

BillingInfoView::~BillingInfoView()
{
    delete ui;
}

void BillingInfoView::on_backButton_clicked()
{
    controller->closeView();
}
