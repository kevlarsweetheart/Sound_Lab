QT += core gui widgets

TEMPLATE = app
TARGET = editor

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$SLABINCLUDE/mathlib
DESTDIR += $$SLABBIN

SOURCES += main.cpp \
    core/workspace.cpp \
    core/track.cpp \
    core/filepart.cpp \
    core/audiofile.cpp \
    mainwindow.cpp \
    filemanager/filemanager.cpp

HEADERS += mainwindow.h \
    core/audio.h \
    filemanager/filemanager.h \

FORMS += \
    mainwindow.ui \
    filemanager/filemanager.ui

LIBS += -L/usr/lib/x86_64-linux-gnu/ -lopenal -lalut

INCLUDEPATH += $$PWD/../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../usr/include

RESOURCES += \
    pics.qrc
