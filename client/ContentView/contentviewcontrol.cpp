#include "contentviewcontrol.h"
#include "../ClientCommunication/successmessage.h"
#include <QDebug>

ContentViewControl::ContentViewControl(ViewControl *vc, ClientDispatcher *d) :
    AbstractViewController(vc, d, CONTENT), contentView(0)
{
    contentView = new ContentView(this);
}

bool ContentViewControl::processMsg(Message *msg)
{
    bool result = true;
    ACTION_TYPE msgAction = msg->getActionType();
    DEST_TYPE msgDest = msg->getDestType();

    if(msgDest != ownDest) {
        qDebug() << "ContentViewControl: Error - received a message for another subsystem.";
        return false;
    }

    // Log success messages
    const SuccessMessage* successMessage = qobject_cast<const SuccessMessage*>(msg);
    if(successMessage != 0) {
        qDebug() << "ContentViewControl: Received success message.";
        return true;
    }

    // At this point, a data message is expected
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    if(dataMessage == 0) {
        qDebug() << "ContentViewControl: Error - received a message which is not of type DataMessage.";
        return false;
    }
    QVector<SerializableQObject*>* data = dataMessage->getData();
    if( data->isEmpty() && msgAction == RETRIEVE ) {
        qDebug() << "ContentViewControl: Message data vector is empty.";

        /* Assume that a content manager requested all books, or that
         * a student requested their book list
         */
        if( viewControl->getCurrentUser()->isOfType(User::CONTENTMGR) ) {
            QVector<Book*>* emptyAllBooks = new QVector<Book*>();
            result = receiveBooks(emptyAllBooks);
            delete emptyAllBooks;
        } else if( viewControl->getCurrentUser()->isOfType(User::STUDENT) ) {
            QVector<SerializableQObject*>* emptyBookList = new QVector<SerializableQObject*>();
            result = receiveBookList(emptyBookList);
            delete emptyBookList;
        } else {
            qDebug() << "ContentViewControl: Error - No operations related to reception of empty data for an admin user.";
            result = false;
        }
        return result;
    } else if( data->isEmpty() ) {
        qDebug() << "ContentViewControl: Error - Message data vector is empty for non-RETRIEVE operation.";
        return false;
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------
    SerializableQObject* item0 = data->first();
    QVectorIterator<SerializableQObject*> itr(*data);
    Book* book = qobject_cast<Book*>(item0);

    switch(msgAction)
    {
    case RETRIEVE:
    {
        qDebug() << "ContentViewControl: received RETRIEVE message.";
        Term* term = qobject_cast<Term*>(item0);
        if( term != 0 ) {
            result = receiveBookList(data);

        } else if( book != 0 ) {
            QVector<Book*>* books = new QVector<Book*>();
            while(itr.hasNext()) {
                book = qobject_cast<Book*>(itr.next());
                if(book == 0) {
                    result = false;
                    qDebug() <<  "ContentViewControl: Error - Processing list of Books, but element is not a Book.";
                    break;
                }
                books->append(book);
            }
            if( result ) {
                result = receiveBooks(books);
            }
            delete books;

        } else {
            qDebug() <<  "ContentViewControl: Error - No operation found for RETRIEVE action given input data.";
            result = false;
        }
        break;
    }
    case CREATE:
    case UPDATE:
    case DELETE:
    case INVALIDACTION:
    default:
        if( static_cast<quint32>(msgAction) == CONTENTHANDLER_RETRIEVE2) {
            qDebug() << "ContentViewControl: received CONTENTHANDLER_RETRIEVE2 message.";

            if( book != 0 ) {
                QVector<ContentItem*>* items = new QVector<ContentItem*>();
                itr.next(); // Advance to second position
                ContentItem* item = 0;
                while(itr.hasNext()) {
                    item = qobject_cast<ContentItem*>(itr.next());
                    if(item == 0) {
                        result = false;
                        qDebug() <<  "ContentViewControl: Error - Processing list of ContentItems, but element is not a ContentItem.";
                        break;
                    }
                    items->append(item);
                }
                if( result ) {
                    result = receiveBookDetails(book, items);
                }
                delete items;

            } else {
                qDebug() <<  "ContentViewControl: Error - first data item is not a Book.";
                result = false;
            }

        } else {
            qDebug() << "ContentViewControl: Error - unexpected message action type.";
            result = false;
        }
        break;
    }

    return result;
}

QWidget* ContentViewControl::getView(){
     return contentView;
 }

// TODO (Remy or Brandon) Stub implementation
bool ContentViewControl::receiveBookList(QVector<SerializableQObject*>* items) {
    return false;
}

// TODO (Remy or Brandon) Stub implementation
bool ContentViewControl::receiveBookDetails(Book* book, QVector<ContentItem*>* items) {
    return false;
}

// TODO (Remy or Brandon) Stub implementation
bool ContentViewControl::receiveBooks(QVector<Book*>* items) {
    return false;
}

void ContentViewControl::addBook(Book* book, Course* course, Term* term) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(book);
    if( course != 0 ) {
        data->append(course);
        if( term != 0 ) {
            data->append(term);
        }
    } else if( term != 0 ) {
        qDebug() << "ContentViewControl::addBook() : Error - Null Course, but non-null Term.";
    }
    sendData(CREATE, data);
}

void ContentViewControl::addChapter(Chapter* chapter) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(chapter);
    sendData(CREATE, data);
}

void ContentViewControl::addSection(ChapterSection* section) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(section);
    sendData(CREATE, data);
}

void ContentViewControl::updateBook(Book* book, Course* course, Term* term) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(book);
    if( course != 0 ) {
        data->append(course);
        if( term != 0 ) {
            data->append(term);
        }
    } else if( term != 0 ) {
        qDebug() << "ContentViewControl::updateBook() : Error - Null Course, but non-null Term.";
    }
    sendData(UPDATE, data);
}

void ContentViewControl::updateChapter(Chapter* chapter) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(chapter);
    sendData(UPDATE, data);
}

void ContentViewControl::updateSection(ChapterSection* section) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(section);
    sendData(UPDATE, data);
}

void ContentViewControl::removeBook(Book* book) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(book);
    sendData(DELETE, data);
}

void ContentViewControl::removeChapter(Chapter* chapter) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(chapter);
    sendData(DELETE, data);
}

void ContentViewControl::removeSection(ChapterSection* section) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(section);
    sendData(DELETE, data);
}

void ContentViewControl::requestBookList(void) {
    if( viewControl->getCurrentUser()->isOfType(User::STUDENT) ) {
        QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
        sendData(RETRIEVE, data);
    } else {
        qDebug() << "ContentViewControl::requestBookList() : Error - current user is not a student.";
    }
}

void ContentViewControl::requestBookDetails(Book* book) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(book);
    sendData(RETRIEVE, data);
}

void ContentViewControl::requestBooks(void) {
    if( viewControl->getCurrentUser()->isOfType(User::CONTENTMGR) ) {
        QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
        sendData(RETRIEVE, data);
    } else {
        qDebug() << "ContentViewControl::requestBooks() : Error - current user is not a content manager.";
    }
}
