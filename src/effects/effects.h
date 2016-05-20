#pragma once
#ifndef EFFECTS_H
#define EFFECTS_H

#include <vector>
#include "service/defines.h"

namespace Effects
{
    class Effect;
    class Distortion;
}

class Effect
{
public:
    Effect();
    virtual ~Effect() = 0;
    virtual std::vector<int> apply_effect(std::vector<int>) = 0;
    int type;
};

class Distortion : public Effect
{
public:
    Distortion();
    void set_distort_val(int value);
    int get_distort_val();
    std::vector<int> apply_effect(std::vector<int> amplitudes);
private:
    int distortion_val;
};

#endif // EFFECTS_H
