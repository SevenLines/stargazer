TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    extension-functions.c

TARGET = ../build/sqlitefunctions

win32: {
    TARGET = ../build/libsqlitefunctions
    TARGET = ../$$TARGET
}

INCLUDEPATH += ../3rdparty/sqlite/

