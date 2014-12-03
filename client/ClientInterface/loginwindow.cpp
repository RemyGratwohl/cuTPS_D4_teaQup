#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "viewcontrol.h"

LoginWindow::LoginWindow(ViewControl *control, QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_connectButton_clicked()
{
    QString username = ui->userNameLineEdit->text();
    controller->authenticateUser(username);
}

