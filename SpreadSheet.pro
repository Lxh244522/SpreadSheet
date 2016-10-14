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
    dialog.cpp \
    spreadsheetdelegate.cpp \
    spreadsheetitem.cpp \
    gotocelldialog.cpp

HEADERS  += mainwindow.h \
    finddialog.h \
    dialog.h \
    spreadsheetdelegate.h \
    spreadsheetitem.h \
    gotocelldialog.h

RESOURCES += \
    image.qrc

FORMS += \
    sortdialog.ui
