#include "contentcontrol.h"
#include "../../client/ClientCommunication/successmessage.h"
#include "../client/ClientCommunication/datamessage.h"
#include <QDebug>

ContentControl::ContentControl(ServerDispatcher *d, CourseControl *courseCtrl)
    : AbstractManager(d), courseControl(courseCtrl), contentStorageControl(0)
{}

bool ContentControl::initialize(void) {
    return ContentStorageControl::getContentStorageControl(contentStorageControl);
}

bool ContentControl::processMsg(const Message *msg)
{
    QString error;
    bool result = false;
    ACTION_TYPE msgAction = INVALIDACTION;

{
    // Input validation concerning the message dispatching
    // ---------------------------------------------------
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    if(dataMessage == 0) {
        error = "ContentControl: Error - received a message which is not of type DataMessage.";
        goto PROCESSMSG_ERROR;
    }

    msgAction = dataMessage->getActionType();
    DEST_TYPE msgDest = dataMessage->getDestType();

    if(msgDest != CONTENT) {
        error = "ContentControl: Error - received a message for another subsystem.";
        goto PROCESSMSG_ERROR;
    }

    // Input validation concerning the content of the message
    // ------------------------------------------------------
    QVector<SerializableQObject*>* data = dataMessage->getData();
    ContentItem* item = 0;
    if( data == 0 && msgAction != RETRIEVE ) {
        error =  "ContentControl: Error - received a message with no data for a non-RETRIEVE action.";
        goto PROCESSMSG_ERROR;
    } else if( data != 0 && data->size() != 1 ) {
        error =  "ContentControl: Error - Message data vector has a length other than 1."
                 " Presently, all messages with data are expected to contain one item.";
        goto PROCESSMSG_ERROR;
    } else {
        item = qobject_cast<ContentItem*>(data->first());
        if( item == 0 ) {
            error =  "ContentControl: Error - Message data vector has a null first element,"
                     " or the first element is not a ContentItem.";
            goto PROCESSMSG_ERROR;
        }
    }

    // Input validation concerning the user
    // ------------------------------------
    User* user = dataMessage->getUser();
    if( !user->isOfType(User::CONTENTMGR) && msgAction != RETRIEVE ) {
        error =  "ContentControl: Error - Non-ContentManager user cannot manage content.";
        goto PROCESSMSG_ERROR;
    } else if( !user->isOfType(User::CONTENTMGR) || !user->isOfType(User::STUDENT) ) {
        error =  "ContentControl: Error - Non-ContentManager and non-Student user cannot access content.";
        goto PROCESSMSG_ERROR;
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------

    Book* book = qobject_cast<Book*>(item);
    Chapter* chapter = qobject_cast<Chapter*>(item);
    ChapterSection* chapterSection = qobject_cast<ChapterSection*>(item);
    QVector<SerializableQObject*>* output = 0;

    switch(msgAction)
    {

    case CREATE:
        qDebug() << "ContentControl: received CREATE message.";
        if( book != 0 ) {
            result =  addBook(book);
        } else if( chapter != 0 ) {
            result =  addChapter(chapter);
        } else if( chapterSection != 0 ) {
            result =  addSection(chapterSection);
        }
        break;

    case RETRIEVE:
        qDebug() << "ContentControl: received RETRIEVE message.";
        if( user->isOfType(User::STUDENT) && item == 0 ) {
            result = getBookList(user, output);
        } else if( book != 0 ) {
            result = getBookDetails(book, output);
        } else if( user->isOfType(User::CONTENTMGR) ) {
            result = getBooks(output);
        } else {
            error =  "ContentControl: Error - No operation found for RETRIEVE action given input data.";
            goto PROCESSMSG_ERROR;
        }
        break;

    case UPDATE:
        qDebug() << "ContentControl: received UPDATE message.";
        if( book != 0 ) {
            result =  updateBook(book);
        } else if( chapter != 0 ) {
            result =  updateChapter(chapter);
        } else if( chapterSection != 0 ) {
            result =  updateSection(chapterSection);
        }
        break;

    case DELETE:
        qDebug() << "ContentControl: received DELETE message.";
        if( book != 0 ) {
            result =  removeBook(book);
        } else if( chapter != 0 ) {
            result =  removeChapter(chapter);
        } else if( chapterSection != 0 ) {
            result =  removeSection(chapterSection);
        }
        break;

    default:
        error =  "ContentControl: received unknown message.";
        goto PROCESSMSG_ERROR;
        break;
    }


    // Dispatch data, if any exists
    Message* outputMsg;
    if( output != 0 ) {
        outputMsg = new DataMessage(CONTENT, msgAction, user, output);
    } else {
        outputMsg = new SuccessMessage(CONTENT, msgAction, user);
    }
    // dispatcher->deliverMsg(outputMsg);
    return result;
}

PROCESSMSG_ERROR:
    qDebug() << error;
    ErrorMessage* outputError = new ErrorMessage(CONTENT, msgAction, user, error);
    // dispatcher->deliverMsg(outputError);
    return result;
}
