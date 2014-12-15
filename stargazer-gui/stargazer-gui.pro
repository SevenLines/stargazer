#-------------------------------------------------
#
# Project created by QtCreator 2014-12-15T18:00:16
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stargazer-gui
TEMPLATE = app

assets.files += assets/GenStar.sqlite
assets.path += $$OUT_PWD/../build/assets

INSTALLS += target

TARGET = ../build/stargazer

INSTALLS += assets

SOURCES += main.cpp\
        mainwindow.cpp \
        star.cpp \
        skyview.cpp \
        sky.cpp

HEADERS  += mainwindow.h \
            star.h \
            skyview.h \
            sky.h

FORMS    += mainwindow.ui

DISTFILES += \
    assets/GenStar.sqlite
