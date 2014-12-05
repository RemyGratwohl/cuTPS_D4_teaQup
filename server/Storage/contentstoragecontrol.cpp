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
    QString courseid = "??";
    QString contentid = "??";
    QString ISBN = book->getISBN();

    // Verify content Item TODO: MOVE ISBN TO CONTENTITEM TABLE
    if(isContentItem(ISBN))
    {
        errorMsg="Content Item ISBN already exists. Please make sure that the Content Item does not already exist.";
        return false;
    }

    // Verify Term
    if(!isTerm(term, termid)){
        // Get latest ID and set that to termid
        termid = QString::number(mainStorage->getLatestID("termid", "term"));
        qDebug() << "Term does not exist! New Term ID: " + termid;
        if(term->getSemester() == "Fall")
            semester = "F";
        else if(term->getSemester() == "Winter")
            semester = "W";
        else if(term->getSemester() == "Summer")
            semester = "S";
        else { // There's an error with the Term object
            errorMsg = "Error with Term object.";
            return false;
        }
        // Add term to DB
        queries.push_back("insert into term (termid, semester, term_year) values (" +
                          termid + ", '" + semester + "', " + QString::number(term->getYear()) + ")");
        qDebug() << queries.at(0);
    }
    else {
        qDebug() << "Term ID: " + termid;
    }

    course->setTermID(termid.toInt());

    // Verify Course
    if(!isCourse(course, courseid)){
        // Get latest ID and set that to courseid
        courseid = QString::number(mainStorage->getLatestID("courseid", "course"));
        qDebug() << "Course does not exist! New Course ID: " + courseid;

        // Add Course to DB
        queries.push_back("insert into course (courseid, name, termid) values (" +
                          courseid + ", '" + course->getName() + "', " + termid + ")");
        qDebug() << queries.last();
    }
    else {
        qDebug() << "Course ID: " + courseid;
    }


    contentid = QString::number(mainStorage->getLatestID("contentid", "contentItem"));
    qDebug() << "New ContentID: " + contentid;

    // Add ContentItem pushback
    queries.push_back("insert into contentItem (title, courseid) values ('" + book->getTitle() + "', " + courseid + ")");
    // Add Book pushback
    queries.push_back("insert into book (contentid, subtitle, authors, publisher, ISBN, website, citation, year_publish) values (" +
                      contentid + ", '" + book->getSubtitle() + "', '" + book->getAuthors() + "', '" +
                      book->getPublisher() + "', '" + book->getISBN() + "', '" + book->getWebsite() + "', '" +
                      book->getCitation() + "', " + QString::number(book->getYearPublished()) + ")");
    // Add Course _ Book Relationship
    queries.push_back("insert into course_book (contentid, courseid) values (" +
                      contentid + ", " + courseid + ")");

    foreach(const QString query, queries)
    {
        qDebug() << "QUERY LIST: " + query;
    }

    // Check for PD, if exists add PD and push back
    if(book->getPurchasingDetails()->getVendor() != NULL)
    {
        // Verify there isn't already a PD for this content Item
    }

    QString response = mainStorage->runTransaction(queries);
    if(response == "success")
    {
        qDebug() << "IT WORKED";
        return true;
    }

    /*
     *
     * Step 3: Verify Purchasing Details
     * Step 4: Add Content Item
     * Step 5: Add Book
     * Step 6: IF PD exists, add it
     * Step 7: If all steps above check out true, then commit & return true else, roll back & return false.
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

bool ContentStorageControl::isTerm(Term *term, QString& id) {

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

bool ContentStorageControl::isCourse(Course* course, QString& id){
    QString query;

    query = "Select courseid from course where termid=" + QString::number(course->getTermID()) + " AND name='" + course->getName() + "'";

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    if(result.first()){
        id = result.value("courseid").toString();
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
bool ContentStorageControl::isContentItem(QString& ISBN) {
    QString query;

    query = "Select ISBN from book where ISBN='" + ISBN + "'";

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    // Just need to check for results
    if(result.first()){
        return true;
    }

    // If there are no results and there were no errors, then the term does not exist.
    else {
        return false;
    }

    query = "Select ISBN from chapter where ISBN='" + ISBN + "'";

    // Run query and get result set object
    result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    // Just need to check for results
    if(result.first()){
        return true;
    }

    // If there are no results and there were no errors, then the term does not exist.
    else {
        return false;
    }

    query = "Select ISBN from chapterSection where ISBN='" + ISBN + "'";

    // Run query and get result set object
    result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    // Just need to check for results
    if(result.first()){
        return true;
    }

    // If there are no results and there were no errors, then the term does not exist.
    else {
        return false;
    }

    //Should never reach here
    qDebug() << "???";
    return false;
}
