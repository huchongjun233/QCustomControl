#-------------------------------------------------
#
# Project created by QtCreator 2022-12-02T10:58:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Drawer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawerwidget.cpp

HEADERS  += mainwindow.h \
    drawerwidget.h

FORMS    += mainwindow.ui \
    equipitempage.ui

RESOURCES += \
    res.qrc


