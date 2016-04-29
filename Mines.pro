#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T14:18:04
#
#-------------------------------------------------

QT       += core gui opengl quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Mines
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    Field.cpp \
    Cell.cpp \
    CellItem.cpp

HEADERS  += MainWindow.hpp \
    Field.hpp \
    Cell.hpp \
    CellItem.hpp

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
