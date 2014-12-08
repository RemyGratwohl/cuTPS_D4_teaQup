#include "billinginfoview.h"
#include "ui_billinginfoview.h"
#include "shoppingcartcontrol.h"
#include "../server/Purchasing/billinginformation.h"

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
    controller->changeActiveView(ShoppingCartControl::SHOPPINGCART);
}

void BillingInfoView::on_orderButton_clicked()
{
    QString name = ui->nameLabel->text();
    QString address = ui->addressLabel->text();
    QString institution = ui->insiutionLabel->text();

    if(name != "" && address != "" && institution != "")
    {
        BillingInformation *info = new BillingInformation(name,address,institution);
        Order *order = new Order(info,controller->getShoppingList());
        controller->processOrder(order);
    }

}
