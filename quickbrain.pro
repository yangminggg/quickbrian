#-------------------------------------------------
#
# Project created by QtCreator 2025-03-01T20:50:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(chess_core/chess_core.pri)
include(chess_ui/chess_ui.pri)
include(chess_model/chess_model.pri)
include(chess_controller/chess_controller.pri)

TARGET = quickbrain
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

INCLUDEPATH += ./eigen

DISTFILES +=
