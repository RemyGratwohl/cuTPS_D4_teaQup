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
    Book* theBook = bookContentTable->getCurrentBook();

    theBook->setTitle(ui->UB_TitleLineEdit->text());
    theBook->setISBN(ui->UB_ISBNLineEdit->text());
    theBook->setImageLink(ui->UB_ImageLinkLineEdit->text());
    theBook->setSubtitle(ui->UB_SubtitleLineEdit->text());
    theBook->setWebsite(ui->UB_WebsiteLineEdit->text());
    theBook->setCitation(ui->UB_CitationPlainTextEdit->toPlainText());
    theBook->setAuthors(ui->UB_AuthorsLineEdit->text());
    theBook->setYearPublished(ui->UB_YearLineEdit->text().toInt());
    PurchasingDetails* pd = theBook->getPurchasingDetails();
    if(pd != 0) {
        pd->setPrice(ui->UB_PriceLineEdit->text().toInt());
        pd->setVendor(ui->UB_VendorLineEdit->text());
    }

    Term * testTerm = new Term(1, "F", 2014);
    Course * testCourse = new Course(1, "CHEM1004: Generic Chemistry", 1);

    controller->updateBook(theBook, testCourse, testTerm);
}

void ContentView::on_UB_CancelButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(LIST);
}

void ContentView::on_AB_ConfirmButton_clicked()
{
    PurchasingDetails* newDetails;

    Term * testTerm = new Term(1, "F", 2014);
    Course * testCourse = new Course(1, "CHEM1004: Generic Chemistry", 1);

    if(ui->AB_PriceLineEdit->text() != "" && ui->AB_VendorLineEdit->text() != "")
    {
     newDetails = new PurchasingDetails(0,ui->AB_PriceLineEdit->text().toInt(),
                                                            ui->AB_VendorLineEdit->text(),0);
    }

    //TODO: Get Course ID
    Book* newBook = new Book(0, ui->AB_TitleLineEdit->text(),
                             1, newDetails, ui->AB_SubtitleLineEdit->text(),
                                            ui->AB_AuthorsLineEdit->text(),
                                            ui->AB_ISBNLineEdit->text(),
                                            ui->AB_WebsiteLineEdit->text(),
                                            ui->AB_YearLineEdit->text().toInt(),
                                            ui->AB_PublisherLineEdit->text(),
                                            ui->AB_CitationPlainTextEdit->toPlainText(),
                                            ui->AB_ImageLinkLineEdit->text());

     controller->addBook(newBook,testCourse, testTerm);
     ui->stackedWidget->setCurrentIndex(LIST);
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
    // Sends a Request to the Server to Add the Chapter Section
    Chapter *newChapter = new Chapter(0,ui->AC_TitleLineEdit->text(),0,0,0,ui->AC_ChapterNumberLineEdit->text().toInt(),ui->AB_ISBNLineEdit->text());

    controller->addChapter(newChapter);
    ui->stackedWidget->setCurrentIndex(UB);
}

void ContentView::on_AC_CancelButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(UB);
}
