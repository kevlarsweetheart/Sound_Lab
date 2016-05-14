#include "audio.h"

using namespace Audio;

FilePart::FilePart(Audiofile *parent_file, QString _name)
{
    this->parent_file = parent_file;
    this->start_time = 0;
    this->file_start = 0;
    this->file_end = parent_file->get_audio_length() - 1;
    this->part_name = _name;
}

FilePart::~FilePart()
{
}

int FilePart::get_lenght()
{
    return this->file_end - this->file_start;
}

int FilePart::get_end_time()
{
    return this->start_time + this->get_lenght();
}
