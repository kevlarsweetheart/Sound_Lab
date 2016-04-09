#pragma once
#ifndef TRACK_H
#define TRACK_H
#include "workspace.h"
#include "plugin.h"
#include <string>

class Track
{
public:
    Track(WorkSpace *owner, int myNum);
    Track(WorkSpace *owner, int myNum, std::string name);
    ~Track();
    void Play();
    void Pause();
    void Stop();
    int AddPlugin(Plugin newPlugin);
    int DeletePlugin(int numOfPlugin);
    int GetNum();
    std::string GetName();
    int ManageMuteState(std::string param);

private:
    int isMuted;
    int volume;
    std::string name;
    int myNum;
    WorkSpace *owner;
};

#endif //TRACK_H
