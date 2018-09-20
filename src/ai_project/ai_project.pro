TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG -= app_bundle

QT -= gui

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

SOURCES += \
    AIBaseClass.cpp \
    GoofBot.cpp \
    goofgamestate.cpp \
    GameObject/gameobject.cpp \
    GameObject/wall.cpp \
    GameObject/crate.cpp \
    GameObject/bomb.cpp \
    GameObject/player.cpp \
    StrategicMaps/iswalkablemap.cpp \
    GameObject/solidifier.cpp \
    StrategicMaps/heatmap.cpp \
    StrategicMaps/traveltimemap.cpp \
    StrategicMaps/blastmap.cpp \   
    DecisionMaker/decisionmaker.cpp \
    DecisionMaker/ialgorithm.cpp \
    DecisionMaker/randomaction.cpp \     
    StrategicMaps/opponentstraveltimemap.cpp \
    locvec.cpp \
    DecisionMaker/safeactionselector.cpp \
    DecisionMaker/offensiveactionselector.cpp \
    bombinfluence.cpp \
    public_define.cpp \
    gooffunctions.cpp

HEADERS += \
    AIBaseClass.h \
    public_define.h \
    GoofBot.h \
    goofgamestate.h \
    GameObject/gameobject.h \
    GameObject/wall.h \
    GameObject/crate.h \
    GameObject/bomb.h \
    GameObject/player.h \
    StrategicMaps/iswalkablemap.h \
    GameObject/solidifier.h \
    StrategicMaps/heatmap.h \
    StrategicMaps/traveltimemap.h \
    StrategicMaps/blastmap.h \    
    DecisionMaker/decisionmaker.h \
    DecisionMaker/ialgorithm.h \
    DecisionMaker/randomaction.h \
    locvec.h \
    DecisionMaker/safeactionselector.h \
    DecisionMaker/offensiveactionselector.h \
    gooffunctions.h
