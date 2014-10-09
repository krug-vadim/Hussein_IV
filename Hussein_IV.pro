QT += core gui widgets
QT += qml quick

TARGET   = Hussein
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14

SOURCES = \
    src/main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/tree/treeview.cpp \
    src/ui/tree/treemodel.cpp \
    src/ui/testtreemodel.cpp

HEADERS = \
    src/ui/mainwindow.h \
    src/ui/tree/treeview.h \
    src/ui/tree/treemodel.h \
    src/core/tree.h \
    src/ui/testtreemodel.h \
    src/interface/treeinterface.h

FORMS   = \
    src/ui/mainwindow.ui

OTHER_FILES +=
