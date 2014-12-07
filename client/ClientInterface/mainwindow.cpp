#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewcontrol.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "../server/ContentManagement/chaptersection.h"

MainWindow::MainWindow(ViewControl *controller) :
    controller(controller),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
