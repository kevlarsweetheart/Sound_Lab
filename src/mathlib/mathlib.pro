QT       -= gui

TARGET = mathlib
TEMPLATE = lib

DEFINES += MATHLIB_LIBRARY

SOURCES += mathlib.cpp

HEADERS += mathlib.h\
        mathlib_global.h

DESTDIR = $$MATHLIB
DLLDESTDIR = $$SLABLIB
target.path += $$DLLDESTDIR
