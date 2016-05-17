#include "audio.h"
#include <cmath>

using namespace Audio;

Track::Track(Workspace *parent, std::string _name, int len, int frequency)
{
    this->parent = parent;
    this->track_name = _name;
    this->compiled_file.file_name = _name + "_WAVE";
    this->is_recordable = true;

    //Building innner audiofile
    struct file_inf buf;
    buf.bit_depth = 16;
    buf.frequency = frequency;
    for(int i = 0; i < len; i++)
    {
        buf.data_left.push_back(0);
        buf.data_right.push_back(0);
    }
    buf.size = len*sizeof(int);
    buf.format = AL_FORMAT_STEREO16;
    this->compiled_file.load_data(buf);

    //Init buffers
    alGenBuffers(1, &Lbuffer);
    alGenBuffers(1, &Rbuffer);
    update_buffer();
}

Track::~Track()
{
}

void Track::compile_track()
{
    std::size_t bound = sound_bricks.size();
    for (std::size_t i = 0; i < bound; ++i)
    {
        struct file_inf aux = sound_bricks[i].parent_file->get_data(sound_bricks[i].file_start,
                                                             sound_bricks[i].file_end);
        int j2 = sound_bricks[i].start_time;
        for(int j1 = 0; j1 < sound_bricks[i].get_lenght(); j1++)
        {
            compiled_file.fdata.data_left[j2] += aux.data_left[j1];
            compiled_file.fdata.data_right[j2] += aux.data_right[j1];
            j2++;
        }
        qDebug() << j2 << "here";
    }
}


std::pair<ALuint, ALuint> Track::get_buffs()
{
    return std::make_pair(this->Lbuffer, this->Rbuffer);
}

void Track::push_brick(Audiofile *_file, QString _name)
{
    sound_bricks.push_back(FilePart(_file, _name));
    compile_track();
    this->parent->unqueue_from_source(this);
    update_buffer();
    this->parent->init_source(this);
}

void Track::update_buffer()
{
    alBufferData(this->Lbuffer, this->compiled_file.fdata.format,
                 this->compiled_file.fdata.data_left.data(),
                 this->compiled_file.fdata.size,
            this->compiled_file.fdata.frequency);

    alBufferData(this->Rbuffer, this->compiled_file.fdata.format,
                 this->compiled_file.fdata.data_right.data(),
                 this->compiled_file.fdata.size,
            this->compiled_file.fdata.frequency);
/*
    qDebug() << compiled_file.fdata.data_right.size() << "left size";
    qDebug() << compiled_file.fdata.data_right.size() << "right size";
    qDebug() << compiled_file.fdata.size << "in bytes";
    qDebug() << compiled_file.fdata.data_right.size() * sizeof(int);
    qDebug() << compiled_file.fdata.format;
    qDebug() << compiled_file.fdata.frequency;
    for(int i = 9961890; i < 9961897; i++)
    {
        qDebug() << compiled_file.fdata.data_left[i] << "left";
        qDebug() << compiled_file.fdata.data_right[i] << "right";
    }*/

    parent->check_errors();
}
