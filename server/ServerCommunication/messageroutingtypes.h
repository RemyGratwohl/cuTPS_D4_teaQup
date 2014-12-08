#ifndef MESSAGEROUTINGTYPES_H
#define MESSAGEROUTINGTYPES_H

enum ACTION_TYPE {CREATE = 0, RETRIEVE, UPDATE, DELETE, INVALIDACTION};
// Content handler subsystem defines a second retrieve constant, value 5
#define CONTENTHANDLER_RETRIEVE2 static_cast<quint32>(5)
// Course handler subsystem defines a second retrieve constant, value 5
#define COURSEHANDLER_RETRIEVE2 static_cast<quint32>(5)

enum DEST_TYPE   {ORDERING = 0, USER, CONTENT, COURSE, INVALIDDEST};

#endif // MESSAGEROUTINGTYPES_H
