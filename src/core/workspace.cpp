#include "audio.h"

using namespace Audio;

Workspace::Workspace(MainWindow *parentWindow)
{
    this->device = alcOpenDevice(NULL);
    this->context = alcCreateContext(device, NULL);
    this->parentWindow = parentWindow;
    this->tempo = 120;
    this->time_signature = std::make_pair(4, 4);

    alListener3f(AL_POSITION, 0, 0, 0);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listener_ori);
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

void Workspace::play()
{
    alSourcePlayv((ALsizei)source_vec.size(), alSources);
}

void Workspace::pause()
{
    alSourcePausev((ALsizei)source_vec.size(), alSources);
}

void Workspace::stop()
{
    alSourceStopv((ALsizei)source_vec.size(), alSources);
}

void Workspace::add_track()
{
    std::string newbie_name = "Track_" + std::to_string(this->tracks_cnt());
    Audio::Track *newbie = new Audio::Track(this,
                            newbie_name,
                            default_track_len, default_frequency);
    track_source.insert(std::pair<Track*, int>(newbie, 2 * (tracks.size() + 1)));

    ALuint *buff_source = new ALuint [2];
    alGenSources((ALuint)2, buff_source);
    init_source(buff_source[0], std::get<0>(newbie->getBuffs()), -1, 0, 0);
    init_source(buff_source[1], std::get<1>(newbie->getBuffs()), 1, 0, 0);
    source_vec.push_back(buff_source[0]);
    source_vec.push_back(buff_source[1]);
    delete [] buff_source;

    update_source_arr();
    tracks.push_back(newbie);

}

void Workspace::delete_track()
{

}

int Workspace::tracks_cnt()
{
    return this->tracks.size();
}

void Workspace::init_source(ALuint src, ALuint buff, int x, int y, int z)
{
    alSourcef(src, AL_PITCH, 1);
    alSourcef(src, AL_GAIN, 1);
    alSource3f(src, AL_POSITION, x, y, z);
    alSource3f(src, AL_VELOCITY, 0, 0, 0);
    alSourcei(src, AL_LOOPING, AL_FALSE);
    alSourcei(src, AL_BUFFER, buff);
}

void Workspace::update_source_arr()
{
    std::size_t len = source_vec.size();
    alSources = new ALuint [len];
    for (std::size_t i = 0; i < len; ++i)
        alSources[i] = source_vec[i];
}
