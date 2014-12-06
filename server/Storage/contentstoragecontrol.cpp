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

    QVector<QSqlQuery> queries;
    QString termid = "??";
    bool existsTerm = true;
    bool existsCourse = true;
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
        existsTerm = false;
        qDebug() << "Term does not exist!";
        // Get latest ID and set that to termid
        termid = QString::number(mainStorage->getLatestID("termid", "term"));
        if(term->getSemester() == "Fall")
            semester = "F";
        else if(term->getSemester() == "Winter")
            semester = "W";
        else if(term->getSemester() == "Summer")
            semester = "S";
        else {
            // There's an error with the Term object
            errorMsg = "Error with Term object.";
            return false;
        }
    }
    else {
        qDebug() << "Term ID: " + termid;
    }



    // Verify Course
    course->setTermID(termid.toInt());

    if(!isCourse(course, courseid)){
        existsCourse = false;
        qDebug() << "Course does not exist!";
        // Get latest ID and set that to courseid
        courseid = QString::number(mainStorage->getLatestID("courseid", "course"));
    }
    else {
        qDebug() << "Course ID: " + courseid;
    }

    // Needs to be replaced with some that gets the id that was inserted. Autoincrement does not strictly increment.
    // It may decided to add a number in the middle.
    contentid = QString::number(mainStorage->getLatestID("contentid", "contentItem"));
    qDebug() << "New ContentID: " + contentid;

    if(mainStorage->getMainStorage().open()){
        mainStorage->getMainStorage().transaction();
        QSqlQuery prepQ;
        if(!existsTerm){

            qDebug() << "Preparing Term";
            // Add term to DB
            prepQ.prepare("insert into term (termid, semester, term_year) values (:termid, :semester, :term_year)");
            prepQ.bindValue(":termid", termid.toInt());
            prepQ.bindValue(":semester", semester);
            prepQ.bindValue(":term_year", term->getYear());
            if(prepQ.exec()){
                qDebug() << "CISC | (Term)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
            }
            else{
                mainStorage->getMainStorage().rollback();
                mainStorage->getMainStorage().close();
                qDebug() << "Add Term Failed";
                errorMsg = prepQ.lastError().text();
                return false;
            }
        }

        if(!existsCourse){
            qDebug() << "Preparing Course";
            // Add Course to DB
            prepQ.prepare("insert into course (courseid, name, termid) values (:courseid, :name, :termid)");
            prepQ.bindValue(":termid", termid.toInt());
            prepQ.bindValue(":courseid", courseid.toInt());
            prepQ.bindValue(":name", course->getName());
            if(prepQ.exec()){
                qDebug() << "CISC | (Course)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
            }
            else{
                mainStorage->getMainStorage().rollback();
                mainStorage->getMainStorage().close();
                errorMsg = prepQ.lastError().text();
                return false;
            }
        }

        // Add Content Item
        prepQ.prepare("insert into contentItem (title, courseid) values (:title, :courseid)");
        prepQ.bindValue(":title", book->getTitle());
        prepQ.bindValue(":courseid", courseid.toInt());
        if(prepQ.exec()){
            qDebug() << "CISC | (Content Item)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }

        // Add Book
        prepQ.prepare("insert into book (contentid, subtitle, authors, publisher, ISBN, website, citation, year_publish) values (:contentid, :subtitle, :authors, :publisher, :ISBN, :website, :citation, :year_publish)");
        prepQ.bindValue(":contentid", contentid.toInt());
        prepQ.bindValue(":subtitle", book->getSubtitle());
        prepQ.bindValue(":authors", book->getAuthors());
        prepQ.bindValue(":publisher", book->getPublisher());
        prepQ.bindValue(":ISBN", book->getISBN());
        prepQ.bindValue(":website", book->getWebsite());
        prepQ.bindValue(":citation", book->getCitation());
        prepQ.bindValue(":year_publish", book->getYearPublished());
        if(prepQ.exec()){
            qDebug() << "CISC | (Book)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }

        // Add Course _ Book Relationship
        prepQ.prepare("insert into course_book (contentid, courseid) values (:contentid, :courseid)");
        prepQ.bindValue(":contentid", contentid.toInt());
        prepQ.bindValue(":courseid", courseid.toInt());
        if(prepQ.exec()){
            qDebug() << "CISC | (Course _ Book)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }


        qDebug() << "Made it through";
        mainStorage->getMainStorage().rollback();
        mainStorage->getMainStorage().close();
        return false;
    }
    else{
        errorMsg = "CISC | addBook(): Database failed to open!";
        return false;
    }


    /*// Check for PD, if exists add PD and push back
    if(book->getPurchasingDetails()->getVendor() != NULL)
    {
        // Verify there isn't already a PD for this content Item
    }*/



    /*
     *
     * Step 3: Verify Purchasing Details
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
