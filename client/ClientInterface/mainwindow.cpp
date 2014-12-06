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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shoppingCartButton_clicked()
{
  controller->changeView(ViewControl::SHOPPING_VIEW);
}
