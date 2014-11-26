#include "contentview.h"
#include "ui_contentview.h"

ContentView::ContentView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentView)
{
    ui->setupUi(this);
}

ContentView::~ContentView()
{
    delete ui;
}
