#ifndef QTJSON_H
#define QTJSON_H

// This file performs the required 'Q_DECLARE_METATYPE' for the JSON header file so the required classes can be passed with signals and slots.
// If you do not need this functionality, please include "json/json.h" directly.

#include <QMetaType>
#include "json/json.h"

// Required meta types. Please add others as required and update 'main.cpp' to also run qRegisterMetaType for these.
Q_DECLARE_METATYPE(Json::Value);

#endif // QTJSON_H
