QT -= gui
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = $${AINAME}

INCLUDEPATH += $${top_srcdir}/exe_project/common

# Include static AI lib
INCLUDEPATH += ../ai_project
win32:CONFIG(release, debug|release): LIBS += -L$${top_builddir}/ai_project/release/ -l$${AINAME}
else:win32:CONFIG(debug, debug|release): LIBS += -L$${top_builddir}/ai_project/debug/  -l$${AINAME}

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $${top_builddir}/ai_project/release/lib$${AINAME}.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $${top_builddir}/ai_project/debug/lib$${AINAME}.a

SOURCES += \
    main.cpp \
    common/JsonClientMsg.cpp \
    common/json/jsoncpp.cpp \
    common/JsonBaseMsg.cpp \
    common/JsonObjectsForMsg.cpp \
    common/util.cpp \
    common/clientrunner.cpp

HEADERS += \
    common/JsonClientMsg.h \
    common/json/json.h \
    common/json/json-forwards.h \
    common/JsonBaseMsg.h \
    common/JsonObjectsForMsg.h \
    common/qtjson.h \
    common/define.h \
    common/Logger.h \
    common/util.h \
    common/clientrunner.h
