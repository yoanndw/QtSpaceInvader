QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tp2
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    mainscene.cpp \
    sprite.cpp \
    player.cpp \
    enemy.cpp \
    missile.cpp

HEADERS  += \
    globalconsts.h \
    mainwindow.h \
    mainscene.h \
    sprite.h \
    player.h \
    enemy.h \
    missile.h