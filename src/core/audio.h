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

namespace Audio
{

    struct file_inf {
        std::vector<int> data_left;
        std::vector<int> data_right;
        ALsizei frequency;
        ALenum format;
        ALsizei size;
        short bit_depth;
    };

    class Audiofile
    {
    private:
        struct file_inf fdata;
    public:
        std::string file_name;
        Audiofile();
        ~Audiofile();
        void getName(std::string path); //Gets file name from the path
        bool loadData(std::string path); //Loads data from existing external file
        bool loadData(struct file_inf input); //Loads data from internal non-existing source
        struct file_inf getData(); //Returns data for intermediate editings
    };

    class FilePart
    {
    public:
        FilePart(Audiofile *parentFile);
        ~FilePart();
        int get_end_time();
        int get_lenght();
        int start_time, file_start, file_end;
        Audiofile *parentFile;
    };

    class Track
    {
    public:
        Track(Workspace *parent);
        ~Track();
        bool is_recordable;
        std::string track_name;
        void compile_track();
    private:
        ALuint buffer[2];
        Workspace *parent;
    };

    class Workspace
    {
    public:
        Workspace();
        ~Workspace();
        static void list_audio_devices(const ALCchar *devices);
        void play_all();
        void pause();
        void stop();
        void add_track();
        void delete_track();
        bool addFile(std::string path);
        std::map<std::string, Audiofile*> files;
    private:
        ALCdevice *device;
        ALCcontext * context;
        std::vector<ALuint *>alSources;
        std::vector<Track *> tracks;
        std::pair<int, int> time_signature;
        float tempo;
    };
}

#endif // AUDIO_H
