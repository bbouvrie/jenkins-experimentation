#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T19:57:26
#
#-------------------------------------------------

TEMPLATE = app
QT       += testlib

QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

SOURCES += \
    main.cpp \
    goofbottestclass.cpp \
    gamestatetestclass.cpp \
    gameobjecttestclass.cpp \
    traveltimemaptest.cpp \
    blastmaptestclass.cpp \   
    walkablemaptestclass.cpp \  
    opponentstraveltimemaptestclass.cpp \
    safeactionselectortestclass.cpp \
    offensiveactionselectortestclass.cpp

# Include static AI lib
INCLUDEPATH += ../ai_project
win32:CONFIG(release, debug|release): LIBS += -L$${top_builddir}/ai_project/release/ -l$${AINAME}
else:win32:CONFIG(debug, debug|release): LIBS += -L$${top_builddir}/ai_project/debug/  -l$${AINAME}

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $${top_builddir}/ai_project/release/lib$${AINAME}.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $${top_builddir}/ai_project/debug/lib$${AINAME}.a

INCLUDEPATH += $${top_srcdir}/ai_project
DEPENDPATH += $${top_srcdir}/ai_project

HEADERS += \
    autotest.h \
    goofbottestclass.h \
    gamestatetestclass.h \
    gameobjecttestclass.h \
    traveltimemaptest.h \
    blastmaptestclass.h \  
    walkablemaptestclass.h \   
    opponentstraveltimemaptestclass.h \  
    safeactionselectortestclass.h \
    offensiveactionselectortestclass.h
