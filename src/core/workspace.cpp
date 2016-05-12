#include "audio.h"

using namespace Audio;

Workspace::Workspace(MainWindow *parentWindow)
{
    this->device = alcOpenDevice(NULL);
    this->context = alcCreateContext(device, NULL);
    this->parentWindow = parentWindow;
    this->tempo = 120;
    this->time_signature = std::make_pair(4, 4);

    this->alSources = new ALuint;
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
    std::string newbie_name = "Track_" + std::to_string(this->tracks_cnt());
    Audio::Track *newbie = new Audio::Track(this,
                            newbie_name,
                            default_track_len, default_frequency);
    tracks.push_back(newbie);
    track_source.insert(std::pair<Track*, int>(newbie, 2 * (tracks.size() - 1)));
}

void Workspace::delete_track()
{

}

int Workspace::tracks_cnt()
{
    return this->tracks.size();
}
