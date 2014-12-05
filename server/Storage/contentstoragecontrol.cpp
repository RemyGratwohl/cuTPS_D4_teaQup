#include "contentstoragecontrol.h"

QSharedPointer<ContentStorageControl> ContentStorageControl::contentStorage(new ContentStorageControl());

bool ContentStorageControl::isInitialized = false;
bool ContentStorageControl::initializationAttempted = false;

bool ContentStorageControl::getContentStorageControl(QSharedPointer<ContentStorageControl>& ptr) {
    if( !initializationAttempted ) {
        initializationAttempted = true;
        isInitialized = contentStorage->initialize();
    }
    if( isInitialized ) {
        ptr = contentStorage;
    }
    return isInitialized;
}


ContentStorageControl::ContentStorageControl(void)
{}

bool ContentStorageControl::initialize(void) {
    return MainStorageControl::getMainStorageControl(mainStorage);
}

bool ContentStorageControl::addBook(Book* book, Course* course, Term* term, QString& errorMsg) {
    qDebug() << "Add Book() Called";
    QVector<QString> queries;
    QString termid = "??";
    QString semester = "";

    //Verify Course and Term
    if(!isTerm(term, termid)){
        // Get latest ID and set that to termid;
        termid = QString::number(mainStorage->getLatestID("termid", "term"));
        qDebug() << "Term does not exist! New Term ID: " + termid;
        if(term->getSemester() == "Fall")
            semester = "F";
        else if(term->getSemester() == "Winter")
            semester = "W";
        else if(term->getSemester() == "Summer")
            semester = "S";
        else // There's an error with the Term object
            return false;
        // Add term to DB
        queries.push_back("insert into term (termid, semester, term_year) values (" +
                          termid + ", '" + semester + "', " + QString::number(term->getYear()) + ")");
        qDebug() << queries.at(0);
    }
    else {
        qDebug() << "Term ID: " + termid;
    }


    /*if(!isCourse){
        // Add Course to DB
    }*/


    //int contentid = GetLatestIDFunction();

    // Add ContentItem pushback
    // Add Book pushback
    // Check for PD, if exists add PD and push back

    /*QString response = mainStorage->runTransaction(queries);
    if(response == "success")
    {
        return true;
    }*/
    /* Step 1: Verify Course (add course, if not null, but first add Term, if not null)
     * Step 2: Get ContentID
     * Step 3: Verify Purchasing Details
     * Step 4: Add Content Item
     * Step 5: Add Book
     * Step 6: IF PD exists, add it
     * Step 7: If all steps above check out true, then return true else, roll back.
     *
     */

    return false;
}

bool ContentStorageControl::addChapter(Chapter* chapter, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::addSection(ChapterSection* section, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::updateBook(Book* book, Course* course, Term* term, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::updateChapter(Chapter* chapter, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::updateSection(ChapterSection* section, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::removeBook(Book* book, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::removeChapter(Chapter* chapter, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::removeSection(ChapterSection* section, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::getBook(OBJ_ID_TYPE bookID, Book* book, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::getBookList(User* student, QVector<Book*>*& items, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::getChapters(Book* book, QVector<Chapter*>*& items, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::getSections(Chapter* chapter, QVector<ChapterSection*>*& items, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::getBooks(QVector<Book*>*& items, QString& errorMsg) {
    return false;
}

bool ContentStorageControl::isTerm(Term *term, QString& id){

    QString query;
    QString semester;

    if(term->getSemester() == "Fall")
        semester = "F";
    else if(term->getSemester() == "Winter")
        semester = "W";
    else if(term->getSemester() == "Summer")
        semester = "S";
    else // There's an error with the Term object
        return false;

    query = "Select termid from term where semester='" + semester + "' AND term_year=" + QString::number(term->getYear());

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    if(result.first()){
        id = result.value("termid").toString();
        return true;
    }
    // If there is more than one user returned, return false because something is wrong with the database
    else if (result.next()){
        return false;
    }
    // If there are no results and there were no errors, then the term does not exist.
    else {
        return false;
    }

    //Should never reach here
    qDebug() << "???";
    return false;
}


