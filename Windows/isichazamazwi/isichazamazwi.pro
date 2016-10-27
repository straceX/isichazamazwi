#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T17:38:57
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = isichazamazwi
TEMPLATE = app


SOURCES += main.cpp\
        isichazamazwi.cpp \
    db_operations.cpp \
    nt_operations.cpp

HEADERS  += isichazamazwi.h \
    db_operations.h \
    nt_operations.h

FORMS    += isichazamazwi.ui
