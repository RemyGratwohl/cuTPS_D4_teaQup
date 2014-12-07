#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewcontrol.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "../server/ContentManagement/chaptersection.h"

MainWindow::MainWindow(ViewControl *controller) :
    controller(controller),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    contentItemTable = new ContentItemTable(this, ui->contentWidget);

    //ui->statusLabel->setText(currentUser->getName());

    /*switch(currentUser->getType()){
        case(User::STUDENT):
            //ui->statusLabel->setText("1");
            break;
        case(User::CONTENTMGR):
            break;
        case(User::ADMIN):
            break;
        default:
            break;
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::viewContentItems(QVector<SerializableQObject*>* contentItems)
{
    return contentItemTable->updateTableView(contentItems);
}

void MainWindow::on_shoppingCartButton_clicked()
{
    controller->setShoppingList(contentItemTable->getSelectedItems());
    controller->changeView(ViewControl::SHOPPING_VIEW);
}
