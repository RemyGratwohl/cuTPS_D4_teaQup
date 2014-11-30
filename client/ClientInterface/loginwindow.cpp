#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "../server/UserManagement/user.h"
#include "QMessageBox"

LoginWindow::LoginWindow(QWidget *parent) :
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

    User *user;

    if(authenticator.authenticateUser(username,&user))
    {
        this->hide();
        MainWindow *w = new MainWindow(user);
        w->show();
    }else{
        QMessageBox msgBox;
        msgBox.setText("Error. Invalid User");
        msgBox.exec();
    }
}
