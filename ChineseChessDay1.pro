#-------------------------------------------------
#
# Project created by QtCreator 2021-03-20T13:47:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChineseChessDay1
TEMPLATE = app


SOURCES += main.cpp\
        MyWidget.cpp \
    Board.cpp \
    Stone.cpp

HEADERS  += MyWidget.h \
    Board.h \
    Stone.h

FORMS    += MyWidget.ui
