#-------------------------------------------------
#
# Project created by QtCreator 2016-10-01T19:21:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpreadSheet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    finddialog.cpp \
    gotocelldialog.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    gotocelldialog.h \
    finddialog.h \
    dialog.h

RESOURCES += \
    image.qrc
