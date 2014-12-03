#include "coursemanagementview.h"
#include "ui_coursemanagementview.h"

CourseManagementView::CourseManagementView(CourseViewControl *control, QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::CourseManagementView)
{
    ui->setupUi(this);
}

CourseManagementView::~CourseManagementView()
{
    delete ui;
}
