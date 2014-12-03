#include "serializableqobject.h"

SerializableQObject::~SerializableQObject(void) {}

void SerializableQObject::insertToDataStream(QDataStream &ds, SerializableType type) const
{
    ds << static_cast<quint32>(type);
    for(int i = 0; i < this->metaObject()->propertyCount(); ++i) {
        if(this->metaObject()->property(i).isStored(this)) {
            ds << this->metaObject()->property(i).read(this);
        }
    }
}

void SerializableQObject::extractFromDataStream(QDataStream &ds)
{
    QVariant var;
    for(int i=0; i<this->metaObject()->propertyCount(); ++i) {
        if(this->metaObject()->property(i).isStored(this)) {
            ds >> var;
            this->metaObject()->property(i).write(this, var);
        }
    }
}
