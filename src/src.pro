QT += core gui widgets

TEMPLATE = app
TARGET = editor

INCLUDEPATH += $$SLABINCLUDE/mathlib
DESTDIR += $$SLABBIN

SOURCES += main.cpp \
    core/ctrlpanel.cpp \
    core/toolbar.cpp \
    core/track.cpp \
    core/workspace.cpp \
    core/plugin.cpp \
    mainwindow.cpp

HEADERS += mainwindow.h \
    mainwindow.h \
    core/ctrlpanel.h \
    core/toolbar.h \
    core/track.h \
    core/workspace.h \
    core/plugin.h \
    mainwindow.h



FORMS += \
    mainwindow.ui \
    mainwindow.ui
