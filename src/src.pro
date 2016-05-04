QT += core gui widgets

TEMPLATE = app
TARGET = editor

INCLUDEPATH += $$SLABINCLUDE/mathlib
DESTDIR += $$SLABBIN

SOURCES += main.cpp \
    core/workspace.cpp \
    core/track.cpp \
    core/filepart.cpp \
    core/audiofile.cpp \
    mainwindow.cpp

HEADERS += mainwindow.h \
    mainwindow.h \
    core/audio.h
    mainwindow.h



FORMS += \
    mainwindow.ui

