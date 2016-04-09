#pragma once
#ifndef WORKSPACE_H
#define WORKSPACE_H
#include "track.h"
#include "plugin.h"
#include <vector>
#include <string>

class WorkSpace
{
public:
    WorkSpace(std::string name);
    ~WorkSpace();
    void PlayAll();
    void StopAll();
    void PauseAll();
    int AddTrack(Track newTrack);
    int DeleteTrack(int numOfTrack);
    int AddPlugin(Plugin newPlugin);
    int DeletePlugin(int numOfPlugin);
    std::string GetName();

private:
    int volume;
    std::string name;
    std::vector<Track*> tracks;
    std::vector<GlobalPlugin*> plugins;
};

#endif //WORKSPACE_H
