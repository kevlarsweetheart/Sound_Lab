#include "audio.h"
#include <string>
#include <vector>
#include <iostream>

using namespace Audio;

Audiofile::Audiofile()
{
}

Audiofile::~Audiofile()
{
}

void Audiofile::getName(std::string path)
{
    std::size_t found_pos = path.find_last_of("/\\") + 1;
    if (found_pos <= path.length())
        this->file_name = path.substr(found_pos);
    else
        this->file_name = path;
}

bool Audiofile::loadData(std::string path)
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
    const char *auxPath = path.c_str();

    short numChannels;

    FILE *fp;
    fp = fopen(auxPath, "r");
    fseek(fp, 22, SEEK_SET);
    fread(&numChannels, sizeof(short), 1, fp);

    fseek(fp, 34, SEEK_SET);
    fread(&(this->fdata.bit_depth), sizeof(short), 1, fp);
    fclose(fp);

    //Copy data to left and right channels
    int *intData = reinterpret_cast<int *>(data);
    if(numChannels == 1)
    {
        for(int i = 0; i < this->fdata.size / this->fdata.bit_depth; i++)
        {
            this->fdata.data_left.push_back(intData[i]);
            this->fdata.data_right.push_back(intData[i]);
        }
    }
    if(numChannels == 2)
    {
        for(int i = 0; i < this->fdata.size / this->fdata.bit_depth - 1; i += 2)
            this->fdata.data_left.push_back(intData[i]);
        for(int i = 1; i < this->fdata.size / this->fdata.bit_depth; i += 2)
            this->fdata.data_right.push_back(intData[i]);
    }
}

bool Audiofile::loadData(struct file_inf input)
{
    this->fdata = input;
}

struct file_inf Audiofile::getData()
{
    return this->fdata;
}

int Audiofile::getAudioLength()
{
    return this->fdata.data_right.size();
}
