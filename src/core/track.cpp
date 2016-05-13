#include "audio.h"

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
    buf.data_left = new int[len];
    buf.data_right = new int[len];
    memset(buf.data_left, 0, len*sizeof(int));
    memset(buf.data_right, 0, len*sizeof(int));
    buf.size = len*sizeof(int);
    buf.format = 4355;
    this->compiled_file.loadData(buf);

    //Init buffers
    alGenBuffers(1, &Lbuffer);
    alGenBuffers(1, &Rbuffer);
}

Track::~Track()
{
}

void Track::compile_track()
{
    std::size_t bound = sound_bricks.size();
    for (std::size_t i = 0; i < bound; ++i)
    {
        struct file_inf aux = sound_bricks[i].parent.getData(sound_bricks[i].file_start,
                                                             sound_bricks[i].file_end);
    }
}

std::pair<ALuint, ALuint> Track::getBuffs()
{
    return std::make_pair(this->Lbuffer, this->Rbuffer);
}

void Track::pushBrick(Audiofile *_file, QString _name)
{
    sound_bricks.push_back(FilePart(_file, _name));
}

void Track::updateBuffer()
{
    alBufferData(this->Lbuffer, this->compiled_file.fdata.format,
                 this->compiled_file.fdata.data_left,
                 this->compiled_file.getAudioLength() * sizeof this->compiled_file.fdata.data_left[0],
            this->compiled_file.fdata.frequency);

    alBufferData(this->Rbuffer, this->compiled_file.fdata.format,
                 this->compiled_file.fdata.data_right,
                 this->compiled_file.getAudioLength() * sizeof this->compiled_file.fdata.data_right[0],
            this->compiled_file.fdata.frequency);
}
