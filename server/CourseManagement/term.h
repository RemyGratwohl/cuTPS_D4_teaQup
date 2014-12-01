#ifndef TERM_H
#define TERM_H

/*
* term.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* Term class:
* - a course must be in a specific term
*
* Traceability: ET-015
*
* Acknowledgements: None
*/

#include "../ServerCommunication/serializableqobject.h"
#include <QString>

class Term : public SerializableQObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 id READ getID WRITE setID)
    Q_PROPERTY(QString semester READ getSemester WRITE setSemester)
    Q_PROPERTY(quint16 year READ getYear WRITE setYear)
public:
    enum SEMESTER { FALL, WINTER, SUMMER };

    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    Term(void);

    /* Constructor
     *   Creates a fully-initialized Term object
     * in: ID
     * in: Semester (expected: F, W, S, Fall, Winter or Summer - case-insensitive)
     * in: Year in which term occurred
     * Side Effects: None
     */
    Term(const quint16 id,
         const QString& semester, const quint16 year);

    /* Member Function: insertToDataStream
     *   Serialization function, which must be overridden to
     *     insert the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

    quint16 getID()   const { return identifier;   }
    void setID(quint16 id)   { identifier = id; }

    /* Member Function: getSemester
     * Side Effects: None
     * Return Value: "Fall", "Winter" or "Summer",
     *   depending on this object's semester
     */
    QString getSemester(void) const;

    /* Member Function: setSemester
     * in: String form of the semester. One of
     *     {F, W, S, Fall, Winter, Summer},
     *     case-insensitive
     * Side Effects: None
     * Return Value: True, if the semester string
     *   is a valid semester, and false otherwise (in which
     *   case, the object is not modified)
     */
    bool setSemester(const QString& s);

    quint16 getYear()   const { return year;   }
    void setYear(quint16 y)   { year = y; }

private:
    quint16 identifier;
    SEMESTER semester;
    quint16 year;
};

#endif // TERM_H
