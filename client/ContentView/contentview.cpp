#include "contentview.h"
#include "ui_contentview.h"

ContentView::ContentView(ContentViewControl *control,QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::ContentView)
{
    ui->setupUi(this);
}

ContentView::~ContentView()
{
    delete ui;
}
