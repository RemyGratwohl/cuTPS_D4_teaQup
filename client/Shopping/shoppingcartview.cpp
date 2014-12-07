#include "shoppingcartview.h"
#include "ui_shoppingcartview.h"
#include "shoppingcartcontrol.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "../server/ContentManagement/chaptersection.h"

ShoppingCartView::ShoppingCartView(ShoppingCartControl *control, QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::ShoppingCartView)
{
    ui->setupUi(this);
    shoppingCartTable = new ShoppingCartTable(this, ui->contentWidget);
}

ShoppingCartView::~ShoppingCartView()
{
    delete ui;
}

bool ShoppingCartView::viewContentItems(QVector<ContentItem*>* contentList)
{
    shoppingCartTable->updateTableView(contentList);
}

void ShoppingCartView::on_orderButton_clicked()
{

}
