#include "coursemanagementview.h"
#include "ui_coursemanagementview.h"
#include "courseviewcontrol.h"

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

void CourseManagementView::on_switchToContentButton_clicked()
{
    controller->switchToNewView(ViewControl::CONTENT_VIEW);
}
