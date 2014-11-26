#include "coursemanagementview.h"
#include "ui_coursemanagementview.h"

CourseManagementView::CourseManagementView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseManagementView)
{
    ui->setupUi(this);
}

CourseManagementView::~CourseManagementView()
{
    delete ui;
}
