TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    extension-functions.c

TARGET = ../build/sqlitefunctions

INCLUDEPATH += ../3rdparty/sqlite/

