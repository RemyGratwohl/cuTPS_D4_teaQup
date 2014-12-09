#include "contentview.h"
#include "ui_contentview.h"
#include "contentviewcontrol.h"

ContentView::ContentView(ContentViewControl *control, QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::ContentView)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    bookContentTable = new BookContentTable(this, ui->tableWidget);
    bookContentTable->initialize(ui->editBookButton);

    // display a list of content items in main window
    QVector<SerializableQObject*>* list = new QVector<SerializableQObject*>();

    Book* testBook = new Book(-1, "The Host", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<SerializableQObject*>(testBook));

    testBook = new Book(-1, "The Hostee", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<SerializableQObject*>(testBook));

    testBook = new Book(-1, "The Hoster", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<SerializableQObject*>(testBook));

    testBook = new Book(-1, "The Hosterer", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<SerializableQObject*>(testBook));

    //viewContentItems(list);
}

ContentView::~ContentView()
{
    delete ui;
}

bool ContentView::viewContentItems(QVector<Book*>* contentItems)
{
    return bookContentTable->updateTableView(contentItems);
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
