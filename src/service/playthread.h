#pragma once
#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>
#include "core/audio.h"
#include "mainwindow.h"

namespace Audio {
    class Workspace;
}
class MainWindow;

class PlayThread : public QThread
{
    Q_OBJECT
public:
    PlayThread(Audio::Workspace *workspace, MainWindow *window);
    ~PlayThread();
    void run();

private:
    Audio::Workspace *workspace;
    MainWindow *window;
};

#endif //PLAYTHREAD_H
