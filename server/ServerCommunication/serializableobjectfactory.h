#ifndef SERIALIZABLEOBJECTFACTORY_H
#define SERIALIZABLEOBJECTFACTORY_H

/*
* serializableobjectfactory.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* SerializableObjectFactory class:
* - Used to transfer SerializableQObject objects,
*   and vectors of them, into and out of a QDataStream.
*
* Traceability: CT-043
*
* Acknowledgements: None
*/

#include <QDataStream>
#include <QtDebug>
#include "serializabletypes.h"
#include "../ContentManagement/book.h"
#include "../ContentManagement/chapter.h"
#include "../ContentManagement/chaptersection.h"
#include "../Purchasing/billinginformation.h"
#include "../ContentManagement/purchasingdetails.h"
#include "../Purchasing/order.h"
#include "../UserManagement/user.h"
#include "../CourseManagement/course.h"
#include "../CourseManagement/term.h"
#include "../../client/ClientCommunication/successmessage.h"
#include "../../client/ClientCommunication/errormessage.h"
#include "../../client/ClientCommunication/datamessage.h"

class SerializableObjectFactory
{
public:

    /* Member Function: serializeObject
     *   Serializes the object into the data stream
     * inout: Data output stream
     * in: Object which inherits from SerializableQObject
     * Side Effects: None
     * Return Value: None
     */
    template<typename T> static void serializeObject(QDataStream&, const T&);

    /* Member Function: deserializeObject
     *   Deserializes an object from the data stream, first by
     *   deserializing the type of the object from the stream,
     *   and then by creating an object of the same type
     *   and extracting data into it.
     *   (The type must be one of the constants defined in
     *    serializabletypes.h)
     *
     *   Outputs a null pointer and returns false if the
     *   object cannot be QObject-cast to type 'T'.
     *
     *   The type parameter, 'T', must inherit from SerializableQObject.
     * inout: Data input stream
     * out: Object which inherits from SerializableQObject
     * Side Effects: None
     * Return Value: See above
     */
    template<typename T> static bool deserializeObject(QDataStream&, T*&);

protected:

    /* Member Function: deserializeObjectVector
     *   Equivalent of deserializeObject() for deserializing
     *   vectors of objects.
     *
     *   Outputs a null pointer and returns false if any object
     *   in the stream cannot be QObject-cast to type 'T'.
     *
     *   The size of the vector is expected to be the first
     *   piece of data in the stream.
     *
     * inout: Data input stream
     * out: Vector of objects which inherit from SerializableQObject
     * Side Effects: None
     * Return Value: See above
     */
    template<typename T> static bool deserializeObjectVector(QDataStream&, QVector<T*>*&);
};

template<typename T>
void SerializableObjectFactory::serializeObject(
        QDataStream& ds, const T& data) {
    data.insertToDataStream(ds);
}

template<typename T>
bool SerializableObjectFactory::deserializeObject(
        QDataStream& ds, T*& output) {

    output = 0;
    quint32 serialType;
    ds >> serialType;

    T* obj = 0;

    switch(serialType) {
    case BOOK:
    {
        Book* newBook = new Book();
        newBook->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newBook);
        break;
    }
    case CHAPTER:
    {
        Chapter* newChapter = new Chapter();
        newChapter->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newChapter);
        break;
    }
    case CHAPTERSECTION:
    {
        ChapterSection* newChapterSection = new ChapterSection();
        newChapterSection->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newChapterSection);
        break;
    }
        /* Done within ContentItem::extractFromDataStream()
    case PURCHASEDETAILS:
    {
        PurchasingDetails* newPurchDets = new PurchasingDetails();
        newPurchDets->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newPurchDets);
        break;
    }
    */
    case ORDEROBJ:
    {
        Order* newOrder = new Order();
        newOrder->extractFromDataStream(ds);
        QVector<ContentItem*>* contentItems = 0;
        if(deserializeObjectVector(ds, contentItems) ) {
            if(newOrder->setFirstContents(contentItems)){
                obj = qobject_cast<T*>(newOrder);
            } else {
                QVectorIterator<ContentItem*> i(*contentItems);
                while (i.hasNext()) {
                    delete (i.next());
                }
                delete contentItems;
                delete newOrder;
            }
        } else {
            delete newOrder;
        }
        break;
    }
        /* Done within Order::extractFromDataStream()
    case BILLINGINFO:
    {
        BillingInformation* newBillingInfo = new BillingInformation();
        newBillingInfo->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newBillingInfo);
        break;
    }
    */
    case USEROBJ:
    {
        User* newUser = new User();
        newUser->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newUser);
        break;
    }
    case TERMOBJ:
    {
        Term* newTerm = new Term();
        newTerm->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newTerm);
        break;
    }
    case COURSEOBJ:
    {
        Course* newCourse = new Course();
        newCourse->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newCourse);
        break;
    }
    case ERRORMESSAGE:
    {
        ErrorMessage* newErrorMessage = new ErrorMessage();
        newErrorMessage->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newErrorMessage);
        break;
    }
    case SUCCESSMESSAGE:
    {
        SuccessMessage* newSuccessMessage = new SuccessMessage();
        newSuccessMessage->extractFromDataStream(ds);
        obj = qobject_cast<T*>(newSuccessMessage);
        break;
    }
    case DATAMESSAGE:
    {
        DataMessage* newDataMessage = new DataMessage();
        newDataMessage->extractFromDataStream(ds);
        QVector<SerializableQObject*>* data = 0;
        if(deserializeObjectVector(ds, data) ) {
            if(newDataMessage->setFirstData(data)){
                obj = qobject_cast<T*>(newDataMessage);
            } else {
                QVectorIterator<SerializableQObject*> i(*data);
                while (i.hasNext()) {
                    delete (i.next());
                }
                delete data;
                delete newDataMessage;
            }
        } else {
            delete newDataMessage;
        }
        break;
    }
    default:
    {
        qDebug() << "SerializableObjectFactory::deserializeObject : Type constant of "
                 << serialType
                 << " is not recognized.";
        break;
    }
    }

    if( obj == 0 ) {
        qDebug() << "SerializableObjectFactory::deserializeObject : Failed.";
    } else {
        output = obj;
    }

    return (output != 0);
}

template<typename T>
bool SerializableObjectFactory::deserializeObjectVector(
        QDataStream& ds, QVector<T*>*& data) {

    data = 0;
    QVector<T*>* obj = new QVector<T*>();
    T* element = 0;
    bool good = true;

    quint32 k;
    ds >> k;
    for(quint32 i = 0; i < k; ++i) {
        element = 0;
        if(deserializeObject(ds, element)) {
            obj->push_back(element);
        } else {
            good = false;
            qDebug() << "SerializableObjectFactory::deserializeObjectVector : Failed at index"
                     << i << ".";
            break;
        }
    }

    if(!good) {
        QVectorIterator<T*> i(*obj);
        while (i.hasNext()) {
            delete (i.next());
        }
        delete obj;
        obj = 0;
    } else {
        data = obj;
    }

    return good;
}

#endif // SERIALIZABLEOBJECTFACTORY_H
