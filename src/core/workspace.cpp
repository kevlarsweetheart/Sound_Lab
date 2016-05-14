#include "audio.h"

using namespace Audio;

Workspace::Workspace(MainWindow *parent_window)
{
    this->device = alcOpenDevice(NULL);
    this->context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    this->parent_window = parent_window;
    this->tempo = 120;
    this->time_signature = std::make_pair(4, 4);

    alListener3f(AL_POSITION, 0, 0, 0);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listener_ori);

    check_errors();
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
    alSourcePlayv((ALsizei)source_vec.size(), source_vec.data());
}

void Workspace::pause()
{
    alSourcePausev((ALsizei)source_vec.size(), source_vec.data());
}

void Workspace::stop()
{
    alSourceStopv((ALsizei)source_vec.size(), source_vec.data());
}

void Workspace::add_track()
{
    std::string newbie_name = "Track_" + std::to_string(this->tracks_cnt());
    Audio::Track *newbie = new Audio::Track(this,
                            newbie_name,
                            default_track_len * default_frequency, default_frequency);
    track_source.insert(std::pair<Track*, int>(newbie, 2 * (tracks.size())));

    ALuint *buff_source = new ALuint [2];

    alGenSources((ALuint)2, buff_source);
    init_source(buff_source[0], std::get<0>(newbie->get_buffs()), -1, 0, 0);
    init_source(buff_source[1], std::get<1>(newbie->get_buffs()), 1, 0, 0);
    source_vec.push_back(buff_source[0]);
    source_vec.push_back(buff_source[1]);
    delete [] buff_source;

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

void Workspace::close_openal()
{
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void Workspace::check_errors()
{
    ALenum err_al = alGetError();
    ALenum err_alc = alcGetError(device);
    char* err_al_str = new char[20];
    err_al_str = (char*)alGetString(err_al);
    char* err_alc_str = new char[20];
    err_alc_str = (char*)alcGetString(device, err_alc);
    qDebug() << err_alc_str;
    qDebug() << err_al_str;
}
