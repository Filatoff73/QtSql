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
    table.cpp \
    dialogmy.cpp

HEADERS  += mainwindow.h \
    table.h \
    dialogmy.h

FORMS    += mainwindow.ui
QT       += sql
QT       += core network sql
