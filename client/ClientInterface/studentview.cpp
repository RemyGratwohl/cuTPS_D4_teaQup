#include "studentview.h"
#include "ui_studentview.h"
#include "viewcontrol.h"

#include "../server/ContentManagement/contentitem.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "../server/ContentManagement/chaptersection.h"

StudentView::StudentView(ViewControl *controller) :
    controller(controller),
    ui(new Ui::StudentView)
{
    ui->setupUi(this);
    contentItemTable = new ContentItemTable(this, ui->contentWidget);

    // display a list of content items in main window
    QVector<ContentItem *>* list = new QVector<ContentItem *>();

    Book* testBook = new Book(-1, "The Host", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<ContentItem*>(testBook));

    testBook = new Book(-1, "The Hostee", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<ContentItem*>(testBook));

    testBook = new Book(-1, "The Hoster", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<ContentItem*>(testBook));

    testBook = new Book(-1, "The Hosterer", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<ContentItem*>(testBook));

    Chapter* testChapter = new Chapter(-1, "The Hostererest", 1, new PurchasingDetails(), -1, 1, " 978-0316068048-1");
    list->push_back(qobject_cast<ContentItem*>(testChapter));

    viewContentItems(list);
}

StudentView::~StudentView()
{
    delete ui;
}

bool StudentView::viewContentItems(QVector<ContentItem*>* contentItems)
{
    return contentItemTable->updateTableView(contentItems);
}

bool StudentView::refreshView()
{
    return contentItemTable->refreshTableView();
}

void StudentView::on_shoppingCartButton_clicked()
{
    controller->setShoppingList(contentItemTable->getSelectedItems());
    controller->changeView(ViewControl::SHOPPING_VIEW);
}