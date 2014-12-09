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
    bookContentTable->initialize(ui->List_UpdateButton);

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


void ContentView::on_List_RemoveButton_clicked()
{

}

void ContentView::on_List_AddButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(AB);
}

void ContentView::on_List_UpdateButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(UB);

    Book* theBook = bookContentTable->getCurrentBook();
    ui->UB_TitleLineEdit->setText(theBook->getTitle());
    ui->UB_ISBNLineEdit->setText(theBook->getISBN());
    ui->UB_ImageLinkLineEdit->setText(theBook->getImageLink());
    ui->UB_SubtitleLineEdit->setText(theBook->getSubtitle());
    ui->UB_WebsiteLineEdit->setText(theBook->getWebsite());
    ui->UB_CitationPlainTextEdit->setPlainText(theBook->getCitation());
    ui->UB_AuthorsLineEdit->setText(theBook->getAuthors());
    ui->UB_YearLineEdit->setText(QString::number(theBook->getYearPublished()));
    PurchasingDetails* pd = theBook->getPurchasingDetails();
    if(pd != 0) {
        ui->UB_PriceLineEdit->setText(QString::number(pd->getPrice()));
        ui->UB_VendorLineEdit->setText(pd->getVendor());
    }
}

void ContentView::on_UB_AddChapterButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(AC);
}

void ContentView::on_UB_EditChapterButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(UC);
}

void ContentView::on_UB_RemoveChapterButton_clicked()
{

}

void ContentView::on_UB_UpdateButton_clicked()
{

}

void ContentView::on_UB_CancelButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(LIST);
}

void ContentView::on_AB_ConfirmButton_clicked()
{

}

void ContentView::on_AB_CancelButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(LIST);
}

void ContentView::on_UC_AddSectionButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ACS);
}

void ContentView::on_UC_UpdateSectionButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(UCS);
}

void ContentView::on_UC_RemoveSectionButton_clicked()
{

}

void ContentView::on_UC_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(UB);
}

void ContentView::on_UC_UpdateButton_clicked()
{

}

void ContentView::on_ACS_ConfirmButton_clicked()
{

}

void ContentView::on_ACS_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(UC);
}

void ContentView::on_UCS_UpdateButton_clicked()
{

}

void ContentView::on_UCS_CancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(UC);
}

void ContentView::on_AC_ConfirmButton_clicked()
{

}

void ContentView::on_AC_CancelButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(UB);
}
