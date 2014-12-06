#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewcontrol.h"

MainWindow::MainWindow(ViewControl *controller) :
    controller(controller),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

bool MainWindow::viewContentItems(QVector<SerializableQObject *>* contentList)
{
    int listSize = contentList->size();
    for(int i = 0; i < listSize; ++i) {
        ContentItem* content = qobject_cast<ContentItem*>(contentList->at(i));
        QListWidgetItem* item = new QListWidgetItem(ui->contentWidget, 0);
        item->setText(content->getTitle());
        ui->contentWidget->addItem(item);
    }

    contentList->clear();
    delete contentList;
    contentList = 0;

    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shoppingCartButton_clicked()
{
  controller->changeView(ViewControl::SHOPPING_VIEW);
}
