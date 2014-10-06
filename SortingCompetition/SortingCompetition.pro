TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    SortingCompetition.cpp

HEADERS += \
    SortingCompetition.h

QMAKE_CXXFLAGS += -std=c++11
