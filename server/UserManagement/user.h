#ifndef USER_H
#define USER_H

/*
* user.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* User class:
* - represents either Student, ContentManager, or Administrator
* - is the user of the cuTPS system
*
* Traceability: ET-016
*
* Acknowledgements: None
*/

#include "../ServerCommunication/serializableqobject.h"
#include <QString>
#include "../Storage/idtypes.h"

class User : public SerializableQObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(quint16 type READ getType WRITE setType)
    Q_PROPERTY(OBJ_ID_TYPE id READ getID WRITE setID)
public:

    enum TYPE { ADMIN, STUDENT, CONTENTMGR, INVALID };

    /* Constructor
     *   To be used to create a container for deserialized data.
     *   User type is set to INVALID.
     * Side Effects: None
     */
    User(void);

    /* Constructor
     *   To be used by the client process
     *     to create a User object that gets fully initialized
     *     on the server and then sent back to complete
     *     the authentication process.
     *   User type is set to INVALID.
     * in: User ID
     * Side Effects: None
     */
    User(const OBJ_ID_TYPE id);

    /* Constructor
     *   Creates a fully-initialized User object
     * in: Username
     * in: Type of user
     * in: User ID
     * Side Effects: None
     */
    User(const QString& name, const TYPE type, const OBJ_ID_TYPE id);

    /* Member Function: insertToDataStream
     *   Serialization function, which is overridden to
     *     insert the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

    QString getName() const { return name; }
    void setName(const QString& n) { name = n; }

    quint16 getType()   const { return (quint16)type;   }
    void setType(quint16 t)   { type = static_cast<TYPE>(t); }

    OBJ_ID_TYPE getID()   const { return identifier;   }
    void setID(OBJ_ID_TYPE id)   { identifier = id; }

    /* Member Function: isOfType
     *   Returns true if this user is of the same
     *     type as that indicated by the input parameter
     * in: User role (type) to compare with
     * Side Effects: None
     * Return Value: True, if the user has the same type
     */
    bool isOfType(const TYPE t) const;

signals:

public slots:

private:
    QString name;
    TYPE type;
    OBJ_ID_TYPE identifier;
};

#endif // USER_H
