#include "contentcontrol.h"
#include "../../client/ClientCommunication/successmessage.h"
#include "../client/ClientCommunication/datamessage.h"
#include <QDebug>
#include <QMultiHash>

ContentControl::ContentControl(ServerDispatcher *d, CourseControl *courseCtrl)
    : AbstractManager(d, CONTENT), courseControl(courseCtrl), contentStorageControl(0)
{}

bool ContentControl::initialize(void) {
    return ContentStorageControl::getContentStorageControl(contentStorageControl);
}

bool ContentControl::processMsg(const Message *msg)
{
    QString error;
    ACTION_TYPE msgAction = INVALIDACTION;
    DEST_TYPE msgDest = INVALIDDEST;
    User* user = msg->getUser();

    // Input validation concerning the message dispatching
    // ---------------------------------------------------
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    if(dataMessage == 0) {
        error = "ContentControl: Error - received a message which is not of type DataMessage.";
        return sendError(msgDest, msgAction, user, error);
    }

    msgAction = dataMessage->getActionType();
    msgDest = dataMessage->getDestType();

    if(msgDest != ownDest) {
        error = "ContentControl: Error - received a message for another subsystem.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Input validation concerning the content of the message
    // ------------------------------------------------------
    QVector<SerializableQObject*>* data = dataMessage->getData();
    ContentItem* item = 0;
    if( msgAction != RETRIEVE && data->isEmpty() ) {
        error =  "ContentControl: Error - Message data vector has a length less than 1."
                 " Presently, all messages with data are expected to contain at least one item.";
        return sendError(msgDest, msgAction, user, error);
    } else if( !data->isEmpty() ){
        item = qobject_cast<ContentItem*>(data->first());
        if( item == 0 ) {
            error =  "ContentControl: Error - Message data vector has a null first element,"
                     " or the first element is not a ContentItem.";
            return sendError(msgDest, msgAction, user, error);
        }
    }

    // Input validation concerning the user
    // ------------------------------------

    if( !user->isOfType(User::CONTENTMGR) && msgAction != RETRIEVE ) {
        error =  "ContentControl: Error - Non-ContentManager user cannot manage content.";
        return sendError(msgDest, msgAction, user, error);
    } else if( !user->isOfType(User::CONTENTMGR) && !user->isOfType(User::STUDENT) ) {
        error =  "ContentControl: Error - Non-ContentManager and non-Student user cannot access content.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------
    bool result = true;
    Book* book = qobject_cast<Book*>(item);
    Chapter* chapter = qobject_cast<Chapter*>(item);
    ChapterSection* chapterSection = qobject_cast<ChapterSection*>(item);
    Course* course = 0;
    Term* term = 0;
    QVector<SerializableQObject*>* output = 0;

    switch(msgAction)
    {

    case CREATE:
        qDebug() << "ContentControl: received CREATE message.";
        if( book != 0 ) {
            // Check if a Course and Term are present
            if( data->size() == 2 || data->size() == 3 ) {
                course = qobject_cast<Course*>(data->at(1));
                if( course == 0 ) {
                    error =  "ContentControl: Error - Object after Book to be added is not a Course.";
                    return sendError(msgDest, msgAction, user, error);
                }
            }
            if( data->size() == 3 ) {
                term = qobject_cast<Term*>(data->at(2));
                if( term == 0 ) {
                    error =  "ContentControl: Error - Object after Course to be added (as part of Book addition) is not a Term.";
                    return sendError(msgDest, msgAction, user, error);
                }
            }
            result = addBook(book, course, term, error);
        } else if( chapter != 0 ) {
            result =  addChapter(chapter, error);
        } else if( chapterSection != 0 ) {
            result =  addSection(chapterSection, error);
        }
        break;

    case RETRIEVE:
        qDebug() << "ContentControl: received RETRIEVE message.";
        if( user->isOfType(User::STUDENT) && item == 0 ) {
            result = getBookList(user, output, error);
        } else if( user->isOfType(User::CONTENTMGR) && item == 0 ) {
            result = getBooks(output, error);
        } else if( book != 0 ) {
            result = getBookDetails(book, output, error);
            msgAction = static_cast<ACTION_TYPE>(CONTENTHANDLER_RETRIEVE2);
        } else {
            error =  "ContentControl: Error - No operation found for RETRIEVE action given input data.";
            return sendError(msgDest, msgAction, user, error);
        }
        break;

    case UPDATE:
        qDebug() << "ContentControl: received UPDATE message.";
        if( book != 0 ) {
            // Check if a Course and Term are present
            if( data->size() == 2 || data->size() == 3 ) {
                course = qobject_cast<Course*>(data->at(1));
                if( course == 0 ) {
                    error =  "ContentControl: Error - Object after Book to be updated is not a Course.";
                    return sendError(msgDest, msgAction, user, error);
                }
            }
            if( data->size() == 3 ) {
                term = qobject_cast<Term*>(data->at(2));
                if( term == 0 ) {
                    error =  "ContentControl: Error - Object after Course to be added (as part of Book update) is not a Term.";
                    return sendError(msgDest, msgAction, user, error);
                }
            }
            result =  updateBook(book, course, term, error);
        } else if( chapter != 0 ) {
            result =  updateChapter(chapter, error);
        } else if( chapterSection != 0 ) {
            result =  updateSection(chapterSection, error);
        }
        break;

    case DELETE:
        qDebug() << "ContentControl: received DELETE message.";
        if( book != 0 ) {
            result =  removeBook(book, error);
        } else if( chapter != 0 ) {
            result =  removeChapter(chapter, error);
        } else if( chapterSection != 0 ) {
            result =  removeSection(chapterSection, error);
        }
        break;

    default:
        error =  "ContentControl: received unknown message.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Handle errors
    if( !result ) {
        return sendError(msgDest, msgAction, user, error);
    }

    // Dispatch data, if any exists
    if( output != 0 ) {
        return sendData(msgAction, 0, output);
    } else {
        return sendSuccess(msgAction, user);
    }
}

bool ContentControl::addBook(Book* book, Course* course, Term* term, QString& errorMsg) {
    return contentStorageControl->addBook(book, course, term, errorMsg);
}

bool ContentControl::addChapter(Chapter* chapter, QString& errorMsg) {
    return contentStorageControl->addChapter(chapter, errorMsg);
}

bool ContentControl::addSection(ChapterSection* section, QString& errorMsg) {
    return contentStorageControl->addSection(section, errorMsg);
}

bool ContentControl::updateBook(Book* book, Course* course, Term* term, QString& errorMsg) {
    return contentStorageControl->updateBook(book, course, term, errorMsg);
}

bool ContentControl::updateChapter(Chapter* chapter, QString& errorMsg) {
    return contentStorageControl->updateChapter(chapter, errorMsg);
}

bool ContentControl::updateSection(ChapterSection* section, QString& errorMsg) {
    return contentStorageControl->updateSection(section, errorMsg);
}

bool ContentControl::removeBook(Book* book, QString& errorMsg) {
    return contentStorageControl->removeBook(book, errorMsg);
}

bool ContentControl::removeChapter(Chapter* chapter, QString& errorMsg) {
    return contentStorageControl->removeChapter(chapter, errorMsg);
}

bool ContentControl::removeSection(ChapterSection* section, QString& errorMsg) {
    return contentStorageControl->removeSection(section, errorMsg);
}

bool ContentControl::getBookList(User* student, QVector<SerializableQObject*>*& items, QString& errorMsg) {
    bool result = true;
    items = 0;

    // First retrieve Book list for the student
    QVector<Book*>* books = 0;
    result = contentStorageControl->getBookList(student, books, errorMsg);
    if( !result ) return result;

    // Organize the books by course
    QMultiHash<OBJ_ID_TYPE, Book*> groupedBooks;
    QVectorIterator<Book*> bookItr(*books);
    Book* currentBook = 0;
    while (bookItr.hasNext()) {
        currentBook = bookItr.next();
        groupedBooks.insert(currentBook->getCourseID(), currentBook);
    }

    // Get the list of course IDs
    QList<OBJ_ID_TYPE> courseIDs = groupedBooks.keys();

    // Retrieve the courses
    QVector<Course*>* courses = 0;
    result = courseControl->getCourses(courseIDs, courses, errorMsg);
    if( !result ) {
        bookItr = *books;
        while (bookItr.hasNext()) {
            delete bookItr.next();
        }
        delete books;
        return result;
    }

    // Organize the courses by term
    QMultiHash<OBJ_ID_TYPE, Course*> groupedCourses;
    QVectorIterator<Course*> courseItr(*courses);
    Course* currentCourse = 0;
    while (courseItr.hasNext()) {
        currentCourse = courseItr.next();
        groupedCourses.insert(currentCourse->getTermID(), currentCourse);
    }

    // Get the list of term IDs
    QList<OBJ_ID_TYPE> termIDs = groupedCourses.keys();

    // Retrieve the terms
    QVector<Term*>* terms = 0;
    result = courseControl->getTerms(termIDs, terms, errorMsg);
    if( !result ) {
        bookItr = *books;
        while (bookItr.hasNext()) {
            delete bookItr.next();
        }
        delete books;
        courseItr = *courses;
        while (courseItr.hasNext()) {
            delete courseItr.next();
        }
        delete courses;
        return result;
    }

    // Assemble the results for output
    items = new QVector<SerializableQObject*>();
    QVectorIterator<Term*> termItr(*terms);
    Term* currentTerm = 0;
    OBJ_ID_TYPE termID = 0;
    QHash<OBJ_ID_TYPE, Course*>::iterator termCourseItr;
    OBJ_ID_TYPE courseID = 0;
    QHash<OBJ_ID_TYPE, Book*>::iterator courseBookItr;

    while (termItr.hasNext()) {
        currentTerm = termItr.next();
        termID = currentTerm->getID();
        items->append(currentTerm);

        termCourseItr = groupedCourses.find(termID);
        while (termCourseItr != groupedCourses.end() && termCourseItr.key() == termID) {
            currentCourse = termCourseItr.value();
            courseID = currentCourse->getID();
            items->append(currentCourse);
            ++termCourseItr;

            courseBookItr = groupedBooks.find(courseID);
            while (courseBookItr != groupedBooks.end() && courseBookItr.key() == courseID) {
                currentBook = courseBookItr.value();
                items->append(currentBook);
                ++courseBookItr;
            }
        }
    }

    delete books;
    delete courses;
    delete terms;
    return result;
}

bool ContentControl::getBookDetails(const Book* bookIn, QVector<SerializableQObject*>*& items, QString& errorMsg) {
    bool result = true;
    items = 0;

    // Retrieve the Book
    Book* book = 0;
    result = contentStorageControl->getBook(bookIn->getID(), book, errorMsg);
    if( !result ) return result;

    // Retrieve the Chapters of the Book
    QVector<Chapter*>* chapters = 0;
    result = contentStorageControl->getChapters(book, chapters, errorMsg);
    if( !result ) {
        delete book;
        return result;
    }

    // Retrieve the ChapterSections of each chapter
    QVector<SerializableQObject*>* output = new QVector<SerializableQObject*>();
    output->append(book);

    QVectorIterator<Chapter*> chapterItr(*chapters);
    Chapter* currentChapter = 0;
    QVector<ChapterSection*>* chapterSections = 0;

    while (chapterItr.hasNext()) {
        currentChapter = chapterItr.next();
        output->append(currentChapter);

        chapterSections = 0;
        result = contentStorageControl->getSections(currentChapter, chapterSections, errorMsg);
        if( !result ) {
            QVectorIterator<SerializableQObject*> itemItr(*output);
            while (itemItr.hasNext()) {
                delete itemItr.next();
            }
            delete output;
            return result;
        } else {
            QVectorIterator<ChapterSection*> sectionItr = *chapterSections;
            while(sectionItr.hasNext()) {
                output->append(sectionItr.next());
            }
        }
    }

    return result;
}

bool ContentControl::getBooks(QVector<SerializableQObject*>*& items, QString& errorMsg) {
    QVector<Book*>* books = 0;
    if(!contentStorageControl->getBooks(books, errorMsg)) {
        return false;
    }
    items = new QVector<SerializableQObject*>();
    QVectorIterator<Book*> bookItr(*books);
    while(bookItr.hasNext()) {
        items->append(bookItr.next());
    }
    return true;
}
