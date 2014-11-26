#include "shoppingcartview.h"
#include "ui_shoppingcartview.h"

ShoppingCartView::ShoppingCartView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoppingCartView)
{
    ui->setupUi(this);
}

ShoppingCartView::~ShoppingCartView()
{
    delete ui;
}
