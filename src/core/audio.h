#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <QStringList>
#include "../mainwindow.h"
#include <QDebug>
#include <QObject>
#include "service/playthread.h"
#include "service/defines.h"
#include "effects/effects.h"

#define default_frequency 44100

class MainWindow;
class PlayThread;

namespace Audio
{
    class Audiofile;
    class FilePart;
    class Track;
    class Workspace;
}

struct file_inf {
    std::vector<int> data_left;
    std::vector<int> data_right;
    ALsizei frequency;
    ALenum format;
    ALsizei size;
    short bit_depth;
};

class Audio::Audiofile
{
private:
public:
    struct file_inf fdata;
    std::string file_name;
    Audiofile();
    ~Audiofile();
    void get_name(std::string path); //Gets file name from the path
    bool load_data(std::string path); //Loads data from existing external file
    bool load_data(struct file_inf input); //Loads data from internal not saved source
    struct file_inf get_data(); //Returns data for intermediate editings
    struct file_inf get_data(int start_index, int end_index);
    int get_audio_length(); //Returns length of data array of audiofile
};

class Audio::FilePart
{
public:
    FilePart(Audiofile *parent_file, QString _name);
    ~FilePart();
    QString part_name;
    int get_end_time(); //Returns the right bound of file part in the track
    int get_lenght(); //Returns length of a file part in number of elements in data array
    int start_time, file_start, file_end;
    std::vector<Effect *> effs;
    void add_effect(Effects::Effect *eff);
    Audiofile *parent_file;
};

class Audio::Track
{
public:
    Track(Audio::Workspace *parent, std::string _name, int len, int frequency);
    ~Track();
    bool is_recordable;
    std::string track_name;
    Audio::Audiofile compiled_file;
    void compile_track();
    std::pair<ALuint, ALuint> get_buffs();
    std::vector<Audio::FilePart> sound_bricks;
    void push_brick(Audio::Audiofile *_file, QString _name);    //Add file part to track
private:
    ALuint Lbuffer, Rbuffer;
    Workspace *parent;
    void update_buffer();   //updates buffers
};

class Audio::Workspace
{
public:
    Workspace(MainWindow *parent_window);
    ~Workspace();
    QStringList list_capture_devices(); //Returns a QStringList of available capture devices
    void play();
    void pause();
    void stop();
    void add_track();
    void delete_track();
    int tracks_cnt();
    void init_source(ALuint src, ALuint buff, int x, int y, int z);
    void init_source(Track *t);
    void unqueue_from_source(Track *t);
    std::map<std::string, Audiofile*> files;
    std::vector<Track *> tracks;
    std::map<Track*, int > track_source; //Track to num of left source map
    void close_openal();
    void check_errors();
    float get_offset_playback(int type);
    int curr_offset = 0;    //in samples
    bool get_playing_state();

private:
    ALCdevice *device;
    ALCcontext *context;
    int default_track_len = 380;              //in seconds
    bool is_playing;
    MainWindow *parent_window;
    std::pair<int, int> time_signature;
    float tempo;
    ALfloat listener_ori[6] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
    std::vector<ALuint> source_vec;
    PlayThread *play_tread;
};

#endif // AUDIO_H
