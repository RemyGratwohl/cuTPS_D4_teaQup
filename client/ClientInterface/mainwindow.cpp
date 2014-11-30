#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(User *user, QWidget *parent) :
    currentUser(user),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusLabel->setText(currentUser->getName());

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

