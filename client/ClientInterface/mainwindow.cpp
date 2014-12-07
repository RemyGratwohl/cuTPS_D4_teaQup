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

bool MainWindow::addView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    ui->stackedWidget->setCurrentWidget(widget);
}

bool MainWindow::popView()
{
    ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
}
