#-------------------------------------------------
#
# Project created by QtCreator 2014-12-15T18:00:16
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

assets.files += assets/*
assets.path += $$OUT_PWD/../build/assets
INSTALLS += assets

sql_assets.files += sql/*
sql_assets.path += $$OUT_PWD/../build/sql
INSTALLS += sql_assets


TARGET = ../build/stargazer
win32: {
    TARGET = ../$$TARGET
}

SOURCES += main.cpp\
        mainwindow.cpp \
        star.cpp \
        skyview.cpp \
        sky.cpp \
    qstaritem.cpp

HEADERS  += mainwindow.h \
            star.h \
            skyview.h \
            sky.h \
    qstaritem.h

FORMS    += mainwindow.ui

DISTFILES += \
    assets/GenStar.sqlite \
    sql/ortogonal.sql \
    sql/load_extension.sql \
    sql/stars.sql \
    sql/edges.sql
