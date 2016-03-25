QT += core
QT -= gui

TARGET = corelib
TEMPLATE = lib

DEFINES += RUSTY_LIBRARY

SOURCES += \
        track.cpp
HEADERS += \
        track.h \
        track_global.h

DESTDIR = $$CORELIB
DLLDESTDIR = $$SLABBIN
target.path += $$DLLDESTDIR
INCLUDEPATH +=$$SLABINCLUDE/corelib
