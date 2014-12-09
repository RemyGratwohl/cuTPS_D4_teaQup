#include "contentview.h"
#include "ui_contentview.h"
#include "contentviewcontrol.h"

ContentView::ContentView(ContentViewControl *control,QWidget *parent) :
    controller(control),
    QWidget(parent),
    ui(new Ui::ContentView)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

ContentView::~ContentView()
{
    delete ui;
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
    Chapter *newChapter = new Chapter(0,ui->AC_TitleLineEdit->text(),0,0,0,ui->AC_ChapterNumberLineEdit->text(),ui->AB_ISBNLineEdit->text());

    controller->addChapter(newChapter);
    ui->stackedWidget->setCurrentIndex(UB);
}

void ContentView::on_AC_CancelButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(UB);
}
