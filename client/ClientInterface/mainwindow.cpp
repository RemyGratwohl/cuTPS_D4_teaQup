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
    ui->contentWidget->setColumnCount(3);
    QTableWidgetItem* firstColumn = new QTableWidgetItem("Title");
    QTableWidgetItem* secondColumn = new QTableWidgetItem("Content Type");
    QTableWidgetItem* thirdColumn = new QTableWidgetItem("Course ID");
    ui->contentWidget->setHorizontalHeaderItem(0, firstColumn);
    ui->contentWidget->setHorizontalHeaderItem(1, secondColumn);
    ui->contentWidget->setHorizontalHeaderItem(2, thirdColumn);

    //ui->statusLabel->setText(currentUser->getName());

    /*switch(currentUser->getType()){
        case(User::STUDENT):
            //ui->statusLabel->setText("1");
            break;
        case(User::CONTENTMGR):
            break;
        case(User::ADMIN):
            break;
        default:
            break;
    }*/
}

bool MainWindow::viewContentItems(QVector<SerializableQObject *>* contentList)
{
    int listSize = contentList->size();
    for(int i = 0; i < listSize; ++i) {
        ContentItem* content = qobject_cast<ContentItem*>(contentList->at(i));

        QTableWidgetItem* itemTitle;
        QTableWidgetItem* itemType;
        QTableWidgetItem* itemCourseID;

        itemTitle = new QTableWidgetItem(content->getTitle());
        itemCourseID = new QTableWidgetItem((quint64)content->getCourseID());

        Book* book = 0;
        Chapter* chapter = 0;
        ChapterSection* chapterSection = 0;
        if((book = qobject_cast<Book*>(content)) != 0) {
            itemType = new QTableWidgetItem("Book");
        } else if((chapter = qobject_cast<Chapter*>(content)) != 0) {
            itemType = new QTableWidgetItem("Chapter");
        } else if((chapterSection = qobject_cast<ChapterSection*>(content)) != 0) {
            itemType = new QTableWidgetItem("ChapterSection");
        }

        ui->contentWidget->setRowCount(listSize);
        ui->contentWidget->setItem(i, 0, itemTitle);
        ui->contentWidget->setItem(i, 1, itemType);
        ui->contentWidget->setItem(i, 2, itemCourseID);
    }

    QVectorIterator<SerializableQObject*> i(*contentList);
    while (i.hasNext()) {
        delete (i.next());
    }
    delete contentList;
    contentList = 0;

    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shoppingCartButton_clicked()
{
  controller->changeView(ViewControl::SHOPPING_VIEW);
}
