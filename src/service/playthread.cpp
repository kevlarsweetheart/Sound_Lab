#include "service/playthread.h"

PlayThread::PlayThread(Audio::Workspace *workspace, MainWindow *window)
{
    this->workspace = workspace;
    this->window = window;
}

PlayThread::~PlayThread()
{

}

void PlayThread::run()
{
    while(workspace->get_playing_state() == true)
    {
        window->set_playback_lcd(workspace->get_offset_playback() * default_frequency);
    }
}
