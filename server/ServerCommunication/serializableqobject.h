#ifndef SERIALIZABLEQOBJECT_H
#define SERIALIZABLEQOBJECT_H

#include <QObject>
#include <QDataStream>
#include <QMetaProperty>
#include <QVariant>
#include "serializabletypes.h"

class SerializableQObject : public QObject
{
Q_OBJECT
public:
    explicit SerializableQObject(QObject *parent = 0);

protected:
    virtual void insertToDataStream(QDataStream& ds, SerializableType type) const;

public:
    virtual void insertToDataStream(QDataStream& ds) const = 0;
    virtual void extractFromDataStream(QDataStream& ds);
};

QDataStream& operator<<(QDataStream&, const SerializableQObject&);
QDataStream& operator>>(QDataStream&, SerializableQObject**);

#endif // SERIALIZABLEQOBJECT_H
