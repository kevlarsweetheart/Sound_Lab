#include "audio.h"
#include <string>
#include <iostream>

using namespace Audio;

Audiofile::Audiofile()
{
}

Audiofile::~Audiofile()
{
}

std::string Audiofile::parsePath(std::string path)
{
    std::size_t found_pos = path.find_last_of("/\\") + 1;
    return path.substr(found_pos);
}

bool Audiofile::loadData(std::string path)
{
}

bool Audiofile::loadData(struct file_inf input)
{
}
