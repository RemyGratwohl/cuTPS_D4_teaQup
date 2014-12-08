#include "coursemanagementview.h"
#include "ui_coursemanagementview.h"
#include "courseviewcontrol.h"

CourseManagementView::CourseManagementView(CourseViewControl *control, QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::CourseManagementView)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(LIST);
}

CourseManagementView::~CourseManagementView()
{
    delete ui;
}

void CourseManagementView::on_switchToContentButton_clicked()
{
    controller->switchToNewView(ViewControl::CONTENT_VIEW);
}

void CourseManagementView::on_addCourseButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ADD);
}

void CourseManagementView::on_updateCourseButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(UPDATE);
}

void CourseManagementView::on_add_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(LIST);
}

void CourseManagementView::on_update_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(LIST);
}

void CourseManagementView::on_update_Confirmbutton_clicked()
{
    //TODO: Call add on server
}
