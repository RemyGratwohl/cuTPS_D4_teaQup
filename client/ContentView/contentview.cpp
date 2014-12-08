#include "contentview.h"
#include "ui_contentview.h"
#include "contentviewcontrol.h"

ContentView::ContentView(ContentViewControl *control,QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::ContentView)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

ContentView::~ContentView()
{
    delete ui;
}

void ContentView::on_switchToCoursesButton_clicked()
{
    controller->switchToNewView(ViewControl::COURSE_VIEW);
}

void ContentView::on_addButtonButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void ContentView::on_add_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ContentView::on_RemoveBookButton_clicked()
{
    //TODO: Call Server to remove selected Item
}

void ContentView::on_update_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ContentView::on_update_UpdateButton_clicked()
{
    //TODO: UPDATE book info
}

void ContentView::on_UC_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void ContentView::on_UC_AddSectionButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void ContentView::on_ACS_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void ContentView::on_AC_ConfirmButton_clicked()
{

}

void ContentView::on_AC_CancelButton_clicked()
{

}

void ContentView::on_l_UpdateBookButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ContentView::on_UB_addChapterbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
