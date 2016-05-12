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

const int default_track_len = 3000;              //in seconds
const int default_frequency = 44100;

class MainWindow;

namespace Audio
{
    class Audiofile;
    class FilePart;
    class Track;
    class Workspace;
}

struct file_inf {
    int *data_left;
    int *data_right;
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
    void getName(std::string path); //Gets file name from the path
    bool loadData(std::string path); //Loads data from existing external file
    bool loadData(struct file_inf input); //Loads data from internal not saved source
    struct file_inf getData(); //Returns data for intermediate editings
    int getAudioLength(); //Returns length of data array of audiofile
};

class Audio::FilePart
{
public:
    FilePart(Audiofile *parentFile);
    ~FilePart();
    int get_end_time(); //Returns the right bound of file part in the track
    int get_lenght(); //Returns length of a file part in number of elements in data array
    int start_time, file_start, file_end;
    Audiofile *parentFile;
};

class Audio::Track
{
public:
    Track(Workspace *parent, std::string _name, int len);
    ~Track();
    bool is_recordable;
    std::string track_name;
    Audio::Audiofile compiled_file;
    void compile_track();
    std::pair<ALuint, ALuint> getBuffs();
private:
    ALuint Lbuffer, Rbuffer;
    Workspace *parent;
    void updateBuffer();
};

class Audio::Workspace
{
public:
    Workspace(MainWindow *parentWindow);
    ~Workspace();
    QStringList list_capture_devices(); //Returns a QStringList of available capture devices
    void play_all();
    void pause();
    void stop();
    void add_track();
    void delete_track();
    int tracks_cnt();
    std::map<std::string, Audiofile*> files;
private:
    MainWindow *parentWindow;
    ALCdevice *device;
    ALCcontext *context;
    ALuint *alSources;
    std::vector<Track *> tracks;
    std::map<Track*, int > track_source; //Track to num of left source map
    std::pair<int, int> time_signature;
    float tempo;
};

#endif // AUDIO_H
