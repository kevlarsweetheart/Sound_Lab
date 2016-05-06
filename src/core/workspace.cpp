#include "audio.h"

using namespace Audio;

Workspace::Workspace(MainWindow *parentWindow)
{
    this->device = alcOpenDevice(NULL);
    this->context = alcCreateContext(device, NULL);
    this->parentWindow = parentWindow;
    this->tempo = 120;
    this->time_signature = std::make_pair(4, 4);
}

Workspace::~Workspace()
{
}

QStringList Workspace::list_capture_devices()
{
    const ALchar *devices = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
    QStringList capt_lst;
    const ALCchar *device = devices, *next = devices + 1;
    std::size_t len = 0;

    while (device && *device != '\0' && next && *next != '\0')
    {
        capt_lst << device;
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }

    return capt_lst;
}

void Workspace::play_all()
{

}

void Workspace::pause()
{

}

void Workspace::stop()
{

}

void Workspace::add_track()
{

}

void Workspace::delete_track()
{

}

bool Workspace::addFile(std::string path)
{

}
