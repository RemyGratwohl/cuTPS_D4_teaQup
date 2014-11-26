#include "usermanagementview.h"
#include "ui_usermanagementview.h"

UserManagementView::UserManagementView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagementView)
{
    ui->setupUi(this);
}

UserManagementView::~UserManagementView()
{
    delete ui;
}
