QT += core gui

TEMPLATE = app
TARGET = editor

SOURCES += \
        main.cpp

INCLUDEPATH += $$SLABINCLUDE/guilib \
               $$SLABINCLUDE/corelib

DESTDIR = $$SLABBIN

LIBS += -L$$SLABLIB/corelib -L$$SLABLIB/guilib -lcorelib -lguilib
