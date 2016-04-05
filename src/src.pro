QT += core
QT += gui

TEMPLATE = app
TARGET = editor

INCLUDEPATH += $$SLABINCLUDE/mathlib
DESTDIR += $$SLABBIN

SOURCES += main.cpp \
           mainwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    core/ctrlpanel.cpp \
    core/toolbar.cpp \
    core/track.cpp \
    core/workspace.cpp

HEADERS += mainwindow.h \
    mainwindow.h \
    core/ctrlpanel.h \
    core/toolbar.h \
    core/track.h \
    core/workspace.h

LIBS += -L$$SLABLIB/mathlib -lmathlib

FORMS += \
    mainwindow.ui
