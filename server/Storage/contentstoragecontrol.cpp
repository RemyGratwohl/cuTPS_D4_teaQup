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
    if (book->getPurchasingDetails() == NULL || course == NULL || term == NULL){
        errorMsg = "If you sent a null course or term, please send the object until further notice. If it was purchasingDetails, please initialize an empty container: new PurchasingDetails()";
        return false;
    }

    bool existsTerm = true;
    bool existsCourse = true;
    bool existsPurchasing = true;
    QString termid = "??";
    QString semester = "";
    QString courseid = "??";
    QString contentid = "??";
    QString ISBN = book->getISBN();

    // Verify content Item
    if(isContentItem(ISBN))
    {
        errorMsg="Content Item ISBN already exists. Please make sure that the Content Item does not already exist.";
        return false;
    }

    // Verify Term
    if(!isTerm(term, termid)){
        existsTerm = false;

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

    // Verify Course
    course->setTermID(termid.toInt());

    if(!isCourse(course, courseid)){
        existsCourse = false;
        qDebug() << "Course does not exist!";
        // Get latest ID and set that to courseid
        courseid = QString::number(mainStorage->getLatestID("courseid", "course"));
    }

    // No autoincrement in favor of more control
    contentid = QString::number(mainStorage->getLatestID("contentid", "contentItem"));


    // Verify PurchasingDetails
    if(!isPurchasable(contentid)){
        existsPurchasing = false;
    }
    else {
        errorMsg = "Purchasing Details already exist for this Content Item ID: " + contentid;
        return false;
    }

    if(mainStorage->getMainStorage().open()){
        mainStorage->getMainStorage().transaction();
        QSqlQuery prepQ;
        if(!existsTerm){
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
        prepQ.prepare("insert into contentItem (contentid, title, isbn, courseid) values (:contentid, :title, :isbn, :courseid)");
        prepQ.bindValue(":contentid", contentid.toInt());
        prepQ.bindValue(":title", book->getTitle());
        prepQ.bindValue(":isbn", book->getISBN());
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
        prepQ.prepare("insert into book (bid, subtitle, authors, publisher, website, citation, year_publish) values (:contentid, :subtitle, :authors, :publisher, :website, :citation, :year_publish)");
        prepQ.bindValue(":contentid", contentid.toInt());
        prepQ.bindValue(":subtitle", book->getSubtitle());
        prepQ.bindValue(":authors", book->getAuthors());
        prepQ.bindValue(":publisher", book->getPublisher());
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

        if( !existsPurchasing && book->getPurchasingDetails()->getPrice() != 0 && book->getPurchasingDetails()->getVendor() != 0) {
            // Add Purchasing Details
            prepQ.prepare("insert into purchasingDetails (price, vendor, contentid) values (:price, :vendor, :contentid)");
            prepQ.bindValue(":price", book->getPurchasingDetails()->getPrice());
            prepQ.bindValue(":vendor", book->getPurchasingDetails()->getVendor());
            prepQ.bindValue(":contentid", contentid.toInt());

            if(prepQ.exec()){
                qDebug() << "CISC | (Purchasing Details)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
            }
            else{
                mainStorage->getMainStorage().rollback();
                mainStorage->getMainStorage().close();
                errorMsg = prepQ.lastError().text();
                return false;
            }
        }

        if(!mainStorage->getMainStorage().commit())
        {
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = "Commit failed: " + prepQ.lastError().text();
            return false;
        }
        else {
            qDebug() << "Everything went great.";
            mainStorage->getMainStorage().close();
            return true;
        }
    }
    else{
        errorMsg = "CISC | addBook(): Database failed to open!";
        return false;
    }

    return false;
}


// Untested
bool ContentStorageControl::addChapter(Chapter* chapter, QString& errorMsg) {

    bool existsPurchasing = true;

    QString contentid = "??";
    QString ISBN = chapter->getISBN();
    QString courseid = QString::number(chapter->getCourseID());
    QString bookid = QString::number(chapter->getBookID());

    // Verify content Item
    if(isContentItem(ISBN))
    {
        errorMsg="Content Item ISBN already exists. Please make sure that the Content Item does not already exist.";
        return false;
    }

    // No autoincrement in favor of more control
    contentid = QString::number(mainStorage->getLatestID("contentid", "contentItem"));

    // Verify PurchasingDetails
    if(!isPurchasable(contentid)){
        existsPurchasing = false;
    }
    else {
        errorMsg = "Purchasing Details already exist for this Content Item ID: " + contentid;
        return false;
    }

    // Verify book
    if(isBook(bookid)){
        bookid = QString::number(chapter->getBookID());
    }
    else {
        errorMsg = "BookID: " + QString::number(chapter->getBookID()) + " is invalid!";
        return false;
    }

    if(mainStorage->getMainStorage().open()){
        mainStorage->getMainStorage().transaction();
        QSqlQuery prepQ;

        // Add Content Item
        prepQ.prepare("insert into contentItem (contentid, title, isbn, courseid) values (:contentid, :title, :isbn, :courseid)");
        prepQ.bindValue(":contentid", contentid.toInt());
        prepQ.bindValue(":title", chapter->getTitle());
        prepQ.bindValue(":isbn", ISBN);
        prepQ.bindValue(":courseid", courseid.toInt());
        if(prepQ.exec()){
            qDebug() << "CISC | (Content Item | Add Chapter)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }

        // Add Chapter
        prepQ.prepare("insert into chapter(chid, bookid, chapter_num) values (:contentid, :bookid, :chapterNum)");
        prepQ.bindValue(":contentid", contentid.toInt());
        prepQ.bindValue(":bookid", bookid.toInt());
        prepQ.bindValue(":chapterNum", chapter->getChapterNumber());
        if(prepQ.exec()){
            qDebug() << "CISC | (Chapter | Add Chapter)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }


        if( !existsPurchasing && chapter->getPurchasingDetails()->getPrice() != 0 && chapter->getPurchasingDetails()->getVendor() != 0) {
            // Add Purchasing Details
            prepQ.prepare("insert into purchasingDetails (price, vendor, contentid) values (:price, :vendor, :contentid)");
            prepQ.bindValue(":price", chapter->getPurchasingDetails()->getPrice());
            prepQ.bindValue(":vendor", chapter->getPurchasingDetails()->getVendor());
            prepQ.bindValue(":contentid", contentid.toInt());

            if(prepQ.exec()){
                qDebug() << "CISC | (Purchasing Details | Add Chapter)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
            }
            else{
                mainStorage->getMainStorage().rollback();
                mainStorage->getMainStorage().close();
                errorMsg = prepQ.lastError().text();
                return false;
            }
        }

        if(!mainStorage->getMainStorage().commit())
        {
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = "Commit failed: " + prepQ.lastError().text();
            return false;
        }
        else {
            qDebug() << "Everything went great.";
            mainStorage->getMainStorage().close();
            return true;
        }
    }
    else{
        errorMsg = "CISC | addChapter(): Database failed to open!";
        return false;
    }

    return false;
}

bool ContentStorageControl::addSection(ChapterSection* section, QString& errorMsg) {
    bool existsPurchasing = true;

    QString contentid = "??";
    QString ISBN = section->getISBN();
    QString courseid = QString::number(section->getCourseID());
    QString chapterid = QString::number(section->getChapterID());

    // Verify content Item
    if(isContentItem(ISBN))
    {
        errorMsg="Content Item ISBN already exists. Please make sure that the Content Item does not already exist.";
        return false;
    }

    // No autoincrement in favor of more control
    contentid = QString::number(mainStorage->getLatestID("contentid", "contentItem"));

    // Verify PurchasingDetails
    if(!isPurchasable(contentid)){
        existsPurchasing = false;
    }
    else {
        errorMsg = "Purchasing Details already exist for this Content Item ID: " + contentid;
        return false;
    }

    // Verify book
    if(!isChapter(chapterid)){
        errorMsg = "ChapterID: " + QString::number(section->getChapterID()) + " is invalid!";
        return false;
    }

    if(mainStorage->getMainStorage().open()){
        mainStorage->getMainStorage().transaction();
        QSqlQuery prepQ;

        // Add Content Item
        prepQ.prepare("insert into contentItem (contentid, title, isbn, courseid) values (:contentid, :title, :isbn, :courseid)");
        prepQ.bindValue(":contentid", contentid.toInt());
        prepQ.bindValue(":title", section->getTitle());
        prepQ.bindValue(":isbn", ISBN);
        prepQ.bindValue(":courseid", courseid.toInt());
        if(prepQ.exec()){
            qDebug() << "CISC | (Content Item | Add Section)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }

        // Add Section
        prepQ.prepare("insert into chapterSection (sectionid, chapterid, section_num, pageRange) values (:contentid, :chapterid, :sectionNum, '')");
        prepQ.bindValue(":contentid", contentid.toInt());
        prepQ.bindValue(":chapterid", chapterid.toInt());
        prepQ.bindValue(":sectionNum", section->getSectionNumber());
        if(prepQ.exec()){
            qDebug() << "CISC | (Chapter | Add Section)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }


        if( !existsPurchasing && section->getPurchasingDetails()->getPrice() != 0 && section->getPurchasingDetails()->getVendor() != 0) {
            // Add Purchasing Details
            prepQ.prepare("insert into purchasingDetails (price, vendor, contentid) values (:price, :vendor, :contentid)");
            prepQ.bindValue(":price", section->getPurchasingDetails()->getPrice());
            prepQ.bindValue(":vendor", section->getPurchasingDetails()->getVendor());
            prepQ.bindValue(":contentid", contentid.toInt());

            if(prepQ.exec()){
                qDebug() << "CISC | (Purchasing Details | Add Section)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
            }
            else{
                mainStorage->getMainStorage().rollback();
                mainStorage->getMainStorage().close();
                errorMsg = prepQ.lastError().text();
                return false;
            }
        }

        if(!mainStorage->getMainStorage().commit())
        {
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = "Commit failed: " + prepQ.lastError().text();
            return false;
        }
        else {
            qDebug() << "Everything went great.";
            mainStorage->getMainStorage().close();
            return true;
        }
    }
    else{
        errorMsg = "CISC | addSection(): Database failed to open!";
        return false;
    }

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

// Tested a lil bit
bool ContentStorageControl::removeBook(Book* book, QString& errorMsg) {
    QString id = QString::number(book->getID());
    bool Success = removeContentItem(id);
    if(Success){
        return Success;
    }
    else {
        errorMsg = "Remove Book: Something went wrong.";
        return false;
    }
}

// Not tested
bool ContentStorageControl::removeChapter(Chapter* chapter, QString& errorMsg) {
    QString id = QString::number(chapter->getID());
    bool Success = removeContentItem(id);
    if(Success){
        return Success;
    }
    else {
        errorMsg = "Remove Chapter: Something went wrong.";
        return false;
    }
}

// Not tested
bool ContentStorageControl::removeSection(ChapterSection* section, QString& errorMsg) {
    QString id = QString::number(section->getID());
    bool Success = removeContentItem(id);
    if(Success){
        return Success;
    }
    else {
        errorMsg = "Remove Section: Something went wrong.";
        return false;
    }
}

// untested: does not include purchasing details yet
bool ContentStorageControl::getBook(OBJ_ID_TYPE bookID, Book* book, QString& errorMsg) {

    // Build Query
    QString query = "Select contentItem.contentid, contentItem.title, contentItem.isbn, contentItem.courseid, book.subtitle, book.authors, book.publisher, book.website, book.citation, book.year_publish, book.picturelink from contentItem inner join book on book.bid = contentItem.contentid where contentid=" + QString::number(bookID);

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    if(result.lastError().text().length() > 1){
        errorMsg = result.lastError().text();
        return false;
    }

    if(result.first()){
        book = new Book();
        QString title = result.value("title").toString();
        book->setTitle(title);
        QString isbn = result.value("isbn").toString();
        book->setISBN(isbn);
        QString subtitle = result.value("subtitle").toString();
        book->setSubtitle(subtitle);
        QString authors = result.value("authors").toString();
        book->setAuthors(authors);
        QString publisher = result.value("publisher").toString();
        book->setPublisher(publisher);
        QString website = result.value("website").toString();
        book->setWebsite(website);
        QString citation = result.value("citation").toString();
        book->setCitation(citation);
        QString picturelink = result.value("picturelink").toString();
        book->setImageLink(picturelink);
        quint16 year = result.value("year_publish").toInt();
        book->setYearPublished(year);
        quint64 courseid = result.value("courseid").toInt();
        book->setCourseID(courseid);
        book->setID(bookID);
        return true;
    }
    // If there is more than one user returned, return false because something is wrong with the database
    if (result.next()){
        errorMsg = "More than one user returned. Database is corrupted.";
        return false;
    }
    // If there are no results and there were no errors, then the book does not exist.
    errorMsg = "Book does not exist";
    return true;
}

// Untested: does not include purchasing details yet
bool ContentStorageControl::getBookList(User* student, QVector<Book*>*& items, QString& errorMsg) {

    quint64 studentid = student->getID();

    // Build Query
    QString query = "Select contentItem.contentid, contentItem.title, contentItem.isbn, contentItem.courseid, book.subtitle, book.authors, book.publisher, book.website, book.citation, book.year_publish, book.picturelink, purchasingDetails.price, purchasingDetails.vendor, purchasingDetails.purchaseid from contentItem inner join book on book.bid = contentItem.contentid inner join course_user on contentItem.courseid=course_user.coid inner join purchasingDetails on contentItem.contentid=purchasingDetails.contentid where userid=" + QString::number(studentid);

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);


    if(result.lastError().text().length() > 1){
        errorMsg = result.lastError().text();
        return false;
    }
    if(!result.first()){
        // If there are no results and there were no errors, then there are no content items for this user
        errorMsg = "There are no content items for this user.";
        return true;
    }

   items = new QVector<Book*>();

    while(result.next()){
        quint64 purchaseid = result.value("purchaseid").toInt();
        QString vendor = result.value("vendor").toString();
        quint16 price = result.value("price").toFloat();
        quint64 contentid = result.value("contentid").toInt();
        PurchasingDetails* details = new PurchasingDetails(purchaseid, price, vendor, contentid);
        Book * book = new Book(-1, "", -1, details, "", "", "", "", -1, "", "", "");
        QString title = result.value("title").toString();
        book->setTitle(title);
        QString isbn = result.value("isbn").toString();
        book->setISBN(isbn);
        QString subtitle = result.value("subtitle").toString();
        book->setSubtitle(subtitle);
        QString authors = result.value("authors").toString();
        book->setAuthors(authors);
        QString publisher = result.value("publisher").toString();
        book->setPublisher(publisher);
        QString website = result.value("website").toString();
        book->setWebsite(website);
        QString citation = result.value("citation").toString();
        book->setCitation(citation);
        QString picturelink = result.value("picturelink").toString();
        book->setImageLink(picturelink);
        quint16 year = result.value("year_publish").toInt();
        book->setYearPublished(year);
        quint64 courseid = result.value("courseid").toInt();
        book->setCourseID(courseid);
        book->setID(contentid);

        items->push_back(book);
    }


    return true;
}

// untested: without purchasing details
bool ContentStorageControl::getChapters(Book* book, QVector<Chapter*>*& items, QString& errorMsg) {

    quint64 bookid = book->getID();

    // Build Query
    QString query = "Select contentItem.contentid, contentItem.title, contentItem.isbn, contentItem.courseid, chapter.chapter_num from contentItem inner join chapter on chapter.chid = contentItem.contentid where bookid=" + QString::number(bookid);

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    if(result.lastError().text().length() > 1){
        errorMsg = result.lastError().text();
        return false;
    }
    if(!result.first()){
        // If there are no results and there were no errors, then the book does not exist.
        errorMsg = "Book does not exist";
        return true;
    }

    items = new QVector<Chapter*>();
    while(result.next()){

        Chapter* chap = new Chapter();
        quint64 contentid = result.value("contentid").toInt();
        chap->setID(contentid);
        QString title = result.value("title").toString();
        chap->setTitle(title);
        QString isbn = result.value("isbn").toString();
        chap->setISBN(isbn);
        quint64 courseid = result.value("courseid").toInt();
        chap->setCourseID(courseid);
        quint16 chapterNum = result.value("chapter_num").toInt();
        chap->setChapterNumber(chapterNum);
        chap->setBookID(bookid);
        items->push_back(chap);
    }

    return true;
}

// untested: without purchasing details
bool ContentStorageControl::getSections(Chapter* chapter, QVector<ChapterSection*>*& items, QString& errorMsg) {

            quint64 chapterid = chapter->getID();

            // Build Query
            QString query = "Select contentItem.contentid, contentItem.title, contentItem.isbn, contentItem.courseid, chapterSection.section_num from contentItem inner join chapterSection on chapterSection.sectionid = contentItem.contentid where chapterid" + QString::number(chapterid);

            // Run query and get result set object
            QSqlQuery result = mainStorage->runQuery(query);

            if(result.lastError().text().length() > 1){
                errorMsg = result.lastError().text();
                return false;
            }
            if(!result.first()){
                // If there are no results and there were no errors, then the book does not exist.
                errorMsg = "Book does not exist";
                return true;
            }

            items = new QVector<ChapterSection*>();

            while(result.next()){

                ChapterSection* sect = new ChapterSection();
                quint64 contentid = result.value("contentid").toInt();
                sect->setID(contentid);
                QString title = result.value("title").toString();
                sect->setTitle(title);
                QString isbn = result.value("isbn").toString();
                sect->setISBN(isbn);
                quint64 courseid = result.value("courseid").toInt();
                sect->setCourseID(courseid);
                quint16 sectionNum = result.value("section_num").toInt();
                sect->setSectionNumber(sectionNum);
                sect->setChapterID(chapterid);
                items->push_back(sect);
            }

            return true;
}

// Untested: Does not include purchasing details yet
bool ContentStorageControl::getBooks(QVector<Book*>*& items, QString& errorMsg) {

    // Build Query
    QString query = "Select contentItem.contentid, contentItem.title, contentItem.isbn, contentItem.courseid, book.subtitle, book.authors, book.publisher, book.website, book.citation, book.year_publish, book.picturelink from contentItem inner join book on book.bid = contentItem.contentid";
    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    if(result.lastError().text().length() > 1){
        errorMsg = result.lastError().text();
        return false;
    }
    if(!result.first()){
        // If there are no results and there were no errors, then there are no content items
        errorMsg = "There are no content items";
        return true;
    }
    items = new QVector<Book*>();

    while(result.next()){
        Book * book = new Book();
        QString title = result.value("title").toString();
        book->setTitle(title);
        QString isbn = result.value("isbn").toString();
        book->setISBN(isbn);
        QString subtitle = result.value("subtitle").toString();
        book->setSubtitle(subtitle);
        QString authors = result.value("authors").toString();
        book->setAuthors(authors);
        QString publisher = result.value("publisher").toString();
        book->setPublisher(publisher);
        QString website = result.value("website").toString();
        book->setWebsite(website);
        QString citation = result.value("citation").toString();
        book->setCitation(citation);
        QString picturelink = result.value("picturelink").toString();
        book->setImageLink(picturelink);
        quint16 year = result.value("year_publish").toInt();
        book->setYearPublished(year);
        quint64 courseid = result.value("courseid").toInt();
        book->setCourseID(courseid);
        quint64 contentid = result.value("contentid").toInt();
        book->setID(contentid);
        items->push_back(book);
    }


    return true;
}


bool ContentStorageControl::isPurchasable(QString& contentid) {
    QString query = "select contentid from purchasingDetails where contentid=" + contentid;

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    // Just checking for results
    if(result.first()){
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

bool ContentStorageControl::isBook(QString& bookid){
    QString query;

    query = "Select bid from book where bid=" + bookid;

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    if(result.first()){
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

bool ContentStorageControl::isChapter(QString& chapterid){
    QString query;

    query = "Select chid from chapter where chid=" + chapterid;

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    if(result.first()){
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

    query = "Select isbn from contentItem where isbn='" + ISBN + "'";

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

    //Should never reach here
    qDebug() << "???";
    return false;
}

bool ContentStorageControl::removeContentItem(QString& contentid){
    QString query;

    query = "Delete from contentItem where contentid=" + contentid;

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }
    if(result.numRowsAffected()  < 1){
        qDebug() << "Nothing was removed";
    }

    qDebug() << "REMOVED: " + QString::number(result.numRowsAffected());
    return true;


}
