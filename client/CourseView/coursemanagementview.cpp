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

    courseTable = new CourseTable(this, ui->courseTableWidget);
    courseTable->initialize(ui->editCourseButton);


    // display a list of content items in main window
    QVector<Course *>* list = new QVector<Course *>();

    Course* course = new Course(0, "Coursey", 0);
    list->push_back(course);

    course = new Course(1, "Courseeeee", 0);
    list->push_back(course);

    course = new Course(0, "Coursieye", 0);
    list->push_back(course);

    viewContentItems(list);


}

CourseManagementView::~CourseManagementView()
{
    delete ui;
}

bool CourseManagementView::viewContentItems(QVector<Course*>* contentItems)
{
    return courseTable->updateTableView(contentItems);
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

void CourseManagementView::on_removeCourseButton_clicked()
{

}

void CourseManagementView::on_add_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(LIST);
}

void CourseManagementView::on_update_ConfirmButton_clicked()
{

}

void CourseManagementView::on_update_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(LIST);
}
