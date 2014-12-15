TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    extension-functions.c

TARGET = ../build/sqlitefunctions

#include(deployment.pri)
#qtcAddDeployment()

