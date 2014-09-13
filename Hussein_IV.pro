QT += core gui widgets

TARGET   = Hussein
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14

SOURCES = \
    src/main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/models/treemodel.cpp

HEADERS = \
    src/core/tree.h \
    src/ui/mainwindow.h \
    src/ui/models/treemodel.h \
    src/core/tree2.h

FORMS   = \
    src/ui/mainwindow.ui
