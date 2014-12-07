#include "studentview.h"
#include "ui_studentview.h"
#include "viewcontrol.h"

StudentView::StudentView(ViewControl *controller) :
    controller(controller),
    ui(new Ui::StudentView)
{
    ui->setupUi(this);
    contentItemTable = new ContentItemTable(this, ui->contentWidget);
}

StudentView::~StudentView()
{
    delete ui;
}

bool StudentView::viewContentItems(QVector<SerializableQObject*>* contentItems)
{
    return contentItemTable->updateTableView(contentItems);
}

void StudentView::on_shoppingCartButton_clicked()
{
    controller->setShoppingList(contentItemTable->getSelectedItems());
    controller->changeView(ViewControl::SHOPPING_VIEW);
}
