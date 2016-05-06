#include "audio.h"

using namespace Audio;

FilePart::FilePart(Audiofile *parentFile)
{
    this->parentFile = parentFile;
    this->start_time = 0;
    this->file_start = 0;
    this->file_end = parentFile->getAudioLength() - 1;
}

FilePart::~FilePart()
{
}

int FilePart::get_lenght()
{
    return this->file_end - this->file_start + 1;
}

int FilePart::get_end_time()
{
    return this->start_time + this->get_lenght() - 1;
}
