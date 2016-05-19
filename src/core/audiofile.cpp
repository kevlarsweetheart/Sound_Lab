#include "audio.h"
#include <string>
#include <vector>
#include <iostream>
#include <QDebug>

using namespace Audio;

Audiofile::Audiofile()
{
}

Audiofile::~Audiofile()
{
}

void Audiofile::get_name(std::string path)
{
    std::size_t found_pos = path.find_last_of("/\\") + 1;
    if (found_pos <= path.length())
        this->file_name = path.substr(found_pos);
    else
        this->file_name = path;
}

bool Audiofile::load_data(std::string path)
{
    //Convert absolute path into ALbyte format
    ALbyte *file_name = new ALbyte[path.size() + 1];
    std::copy(path.begin(), path.end(), file_name);
    file_name[path.size()] = '\0';

    //Load data from file
    ALvoid *data;
    ALboolean loop;
    alutLoadWAVFile(file_name, &(this->fdata.format), &data, &(this->fdata.size),
                    &(this->fdata.frequency), &loop);
    //const char *aux_path = path.c_str();

    short num_channels;

    if(this->fdata.format == AL_FORMAT_MONO8)
    {
        this->fdata.bit_depth = 8;
        num_channels = 1;
    }
    if(this->fdata.format == AL_FORMAT_MONO16)
    {
        this->fdata.bit_depth = 16;
        num_channels = 1;
    }
    if(this->fdata.format == AL_FORMAT_STEREO8)
    {
        this->fdata.bit_depth = 8;
        num_channels = 2;
    }
    if(this->fdata.format == AL_FORMAT_STEREO16)
    {
        this->fdata.bit_depth = 16;
        num_channels = 2;
    }

    /*
    FILE *fp;
    fp = fopen(aux_path, "r");
    fseek(fp, 22, SEEK_SET);
    fread(&num_channels, sizeof(short), 1, fp);

    fseek(fp, 34, SEEK_SET);
    fread(&(this->fdata.bit_depth), sizeof(short), 1, fp);
    fclose(fp);
    */

    //Copy data to left and right channels
    int *int_data = reinterpret_cast<int *>(data);
    int len = this->fdata.size / sizeof int_data[0];
    if(num_channels == 1)
    {
        for(int i = 0; i < len; ++i)
        {
            this->fdata.data_left.push_back(int_data[i]);
            this->fdata.data_right.push_back(int_data[i]);
        }
    }
    if(num_channels == 2)
    {
        for(int i = 0; i < len / 2; ++i)
        {
            this->fdata.data_left.push_back(int_data[2*i]);
            this->fdata.data_right.push_back(int_data[2*i + 1]);
        }
        this->fdata.size /= 2;
    }
}

bool Audiofile::load_data(struct file_inf input)
{
    this->fdata = input;
}

struct file_inf Audiofile::get_data()
{
    return this->fdata;
}

file_inf Audiofile::get_data(int start_index, int end_index)
{
    struct file_inf aux;
    aux.bit_depth = fdata.bit_depth;;
    aux.format = fdata.format;
    aux.frequency = fdata.frequency;

    std::size_t audio_len = get_audio_length();
    if(end_index >= audio_len)
        end_index = audio_len - 1;
    if(start_index >= audio_len)
        start_index = audio_len - 1;
    std::size_t part_time = end_index - start_index;;
    aux.size = (part_time) * sizeof(int);

    for(int i = start_index; i < end_index; i++)
    {
        aux.data_left.push_back(fdata.data_left[i]);
        aux.data_right.push_back(fdata.data_right[i]);
    }
    return aux;
}

int Audiofile::get_audio_length()
{
    return this->fdata.size / sizeof this->fdata.data_left[0];
}
