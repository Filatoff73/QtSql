#-------------------------------------------------
#
# Project created by QtCreator 2015-01-30T10:12:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SqlViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    table.cpp

HEADERS  += mainwindow.h \
    table.h

FORMS    += mainwindow.ui
QT       += sql
QT       += core network sql
LIBS     += "C:\Program Files\PostgreSQL\9.3\lib\libpq.dll"
INCLUDEPATH += C:\Program Files\PostgreSQL\9.3\lib\
