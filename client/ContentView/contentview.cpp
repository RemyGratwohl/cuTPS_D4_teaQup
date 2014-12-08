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

void ContentView::on_pushButton_2_clicked()
{

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
