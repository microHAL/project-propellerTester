#-------------------------------------------------
#
# Project created by QtCreator 2016-03-13T16:16:51
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++1y

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = propellerTester
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp \
        measurement.cpp \
        database.cpp \
    about.cpp \
    propeller.cpp \
    engine.cpp \
    esc.cpp \
    battery.cpp \
    measurementSetup.cpp

HEADERS  += mainwindow.h \
        qcustomplot.h \
        measurement.h \
        database.h \
    about.h \
    propeller.h \
    engine.h \
    esc.h \
    battery.h \
    measurementSetup.h

FORMS    += mainwindow.ui \
    about.ui
