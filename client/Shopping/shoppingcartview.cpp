#include "shoppingcartview.h"
#include "ui_shoppingcartview.h"
#include "shoppingcartcontrol.h"

ShoppingCartView::ShoppingCartView(ShoppingCartControl *control, QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::ShoppingCartView)
{
    ui->setupUi(this);
}

ShoppingCartView::~ShoppingCartView()
{
    delete ui;
}

void ShoppingCartView::on_orderButton_clicked()
{

}
