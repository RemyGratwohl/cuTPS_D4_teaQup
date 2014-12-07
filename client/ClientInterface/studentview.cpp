#include "studentview.h"
#include "ui_studentview.h"

StudentView::StudentView(ViewControl *controller) :
    controller(controller),
    ui(new Ui::StudentView)
{
    ui->setupUi(this);
}

StudentView::~StudentView()
{
    delete ui;
}
