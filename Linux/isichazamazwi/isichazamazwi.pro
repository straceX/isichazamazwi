#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T16:54:10
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT       += widgets

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
