#ifndef COURSE_H
#define COURSE_H

/*
* course.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* Course class:
* - is a course that a Student user can be enrolled in
*
* Traceability: ET-007
*
* Acknowledgements: None
*/

#include "../ServerCommunication/serializableqobject.h"
#include <QString>

class Course : public SerializableQObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 id READ getID WRITE setID)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(quint16 termID READ getTermID WRITE setTermID)
public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    Course(void);

    /* Constructor
     *   Creates a fully-initialized Course object
     * in: Course ID
     * in: Course name
     * in: ID of term offered
     * Side Effects: None
     */
    Course(const quint16 id,
         const QString& name, const quint16 termID);

    /* Member Function: insertToDataStream
     *   Serialization function, which is overridden to
     *     insert the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

    quint16 getID()   const { return identifier;   }
    void setID(quint16 id)   { identifier = id; }

    QString getName() const { return name; }
    void setName(const QString& n) { name = n; }

    quint16 getTermID()   const { return termID;   }
    void setTermID(quint16 id)   { termID = id; }

private:
    quint16 identifier;
    QString name;
    quint16 termID;
};

#endif // COURSE_H
