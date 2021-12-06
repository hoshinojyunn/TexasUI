#-------------------------------------------------
#
# Project created by QtCreator 2021-11-20T17:31:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Texas
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        texasui.cpp \
    judge.cpp \
    poker.cpp \
    round.cpp \
    game_window.cpp \
    round1.cpp \
    var.cpp \
    round2.cpp \
    round3.cpp

HEADERS += \
        texasui.h \
    judge.h \
    poker.h \
    jackpot.h \
    player.h \
    game_window.h \
    round.h \
    round1.h \
    var.h \
    round2.h \
    round3.h

FORMS += \
    texasui.ui \
    your_poker_1.ui \
    game_window.ui \
    round1.ui \
    round2.ui \
    round3.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
