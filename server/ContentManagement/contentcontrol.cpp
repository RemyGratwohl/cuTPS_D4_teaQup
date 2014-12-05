#include "contentcontrol.h"
#include "../../client/ClientCommunication/successmessage.h"
#include "../client/ClientCommunication/datamessage.h"
#include <QDebug>

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

    if(msgDest != CONTENT) {
        error = "ContentControl: Error - received a message for another subsystem.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Input validation concerning the content of the message
    // ------------------------------------------------------
    QVector<SerializableQObject*>* data = dataMessage->getData();
    ContentItem* item = 0;
    if( data == 0 && msgAction != RETRIEVE ) {
        error =  "ContentControl: Error - received a message with no data for a non-RETRIEVE action.";
        return sendError(msgDest, msgAction, user, error);
    } else if( data != 0 && data->size() < 1 ) {
        error =  "ContentControl: Error - Message data vector has a length less than 1."
                 " Presently, all messages with data are expected to contain at least one item.";
        return sendError(msgDest, msgAction, user, error);
    } else {
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
    } else if( !user->isOfType(User::CONTENTMGR) || !user->isOfType(User::STUDENT) ) {
        error =  "ContentControl: Error - Non-ContentManager and non-Student user cannot access content.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------
    bool result = true;
    Book* book = qobject_cast<Book*>(item);
    Chapter* chapter = qobject_cast<Chapter*>(item);
    ChapterSection* chapterSection = qobject_cast<ChapterSection*>(item);
    QVector<SerializableQObject*>* output = 0;

    switch(msgAction)
    {

    case CREATE:
        qDebug() << "ContentControl: received CREATE message.";
        if( book != 0 ) {
            // Check if a Course and Term are present
            Course* course = 0;
            Term* term = 0;
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
        } else if( book != 0 ) {
            result = getBookDetails(book, output, error);
        } else if( user->isOfType(User::CONTENTMGR) ) {
            result = getBooks(output, error);
        } else {
            error =  "ContentControl: Error - No operation found for RETRIEVE action given input data.";
            return sendError(msgDest, msgAction, user, error);
        }
        break;

    case UPDATE:
        qDebug() << "ContentControl: received UPDATE message.";
        if( book != 0 ) {
            result =  updateBook(book, error);
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
        return sendData(msgAction, user, output);
    } else {
        return sendSuccess(msgAction, user);
    }
}

/*

bool ContentControl::addBook(Book* book, Course* course, Term* term, String& errorMsg);

bool ContentControl::addChapter(Chapter* chapter, QString& errorMsg);

bool ContentControl::addSection(ChapterSection* section, QString& errorMsg);

bool ContentControl::updateBook(Book* book, QString& errorMsg);

bool ContentControl::updateChapter(Chapter* chapter, QString& errorMsg);

bool ContentControl::updateSection(ChapterSection* section, QString& errorMsg);

bool ContentControl::removeBook(Book* book, QString& errorMsg);

bool ContentControl::removeChapter(Chapter* chapter, QString& errorMsg);

bool ContentControl::removeSection(ChapterSection* section, QString& errorMsg);

bool ContentControl::getBookList(User* student, QVector<SerializableQObject*>*& items, QString& errorMsg);

bool ContentControl::getBookDetails(const Book* book, QVector<SerializableQObject*>*& items, QString& errorMsg);

bool ContentControl::getBooks(QVector<SerializableQObject*>*& items, QString& errorMsg);

*/
