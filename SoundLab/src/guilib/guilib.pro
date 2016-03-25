QT = core \
       gui \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guilib
TEMPLATE = lib

DEFINES += GUI_LIBRARY

SOURCES += \
        mainwindow.cpp
HEADERS += \
        mainwindow.h \
    mainwindow_global.h

DESTDIR = $$GUILIB
DLLDESTDIR = $$SLABBIN
target.path += $$DLLDESTDIR

INCLUDEPATH += $$SLABINCLUDE/guilib \
                $$SLABINCLUDE/corelib

LIBS += -L$$SLABLIB/corelib -lcorelib

