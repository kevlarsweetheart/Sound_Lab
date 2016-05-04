#include "audio.h"

using namespace Audio;

Workspace::Workspace()
{
}

Workspace::~Workspace()
{
}

void Workspace::list_audio_devices(const ALCchar *devices)
{
    const ALCchar *device = devices, *next = devices + 1;
    std::size_t len = 0;

    std::cout << "Devices available:" << std::endl;
    std::cout << std::endl;

    while (device && *device != '\0' && next && *next != '\0')
    {
        std::cout << device << std::endl;
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }

    std::cout << "-----------------" << std::endl;
}

void Workspace::play_all()
{

}

void Workspace::pause()
{

}

void Workspace::stop()
{

}

void Workspace::add_track()
{

}

void Workspace::delete_track()
{

}

bool Workspace::addFile(std::string path)
{

}
