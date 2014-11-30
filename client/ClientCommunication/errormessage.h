#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

/*
* errormessage.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* Message class:
* - Message containing an error string
*
* Traceability: CT-041
*
* Acknowledgements: None
*/

#include "message.h"

class ErrorMessage : public Message
{
    Q_OBJECT
    Q_PROPERTY(QString error READ getError WRITE setError)

public:
    /* Constructor
     * in: Destination subsystem
     * in: Verb of the message
     * in: User associated with the message
     *      Can be null for messages that are to be sent to the
     *      client processes.
     *      Treated as a shared pointer.
     * in: Content of the error message
     * Side Effects: None
     */
    ErrorMessage(DEST_TYPE, ACTION_TYPE, User*, const QString& error);

    QString getError() const { return error; }
    void setError(const QString& error) { this->error = error; }

    /* Member Function: insertToDataStream
     *   Serialization function, which inserts the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

private:
    QString error;
};

#endif // ERRORMESSAGE_H
