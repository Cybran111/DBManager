#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T15:49:02
#
#-------------------------------------------------

QT       += core gui

QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBManager
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp \
    choosedb.cpp \
    searchdialog.cpp \
    searchpanel.cpp

HEADERS  += mainwindow.h \
    choosedb.h \
    searchdialog.h \
    searchpanel.h \

FORMS    += mainwindow.ui \
    choosedb.ui \
    searchdialog.ui \
    searchpanel.ui
