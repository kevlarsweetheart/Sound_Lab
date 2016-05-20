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
    void set_amps(std::vector<int> amps);
    virtual ~Effect() = 0;
    std::vector<int> get_amps();
    virtual void apply_effect() = 0;
    std::vector<int> amplitudes;
};

class Distortion : public Effect
{
public:
    Distortion();
    void set_distort_val(int value);
    int get_distort_val();
    void apply_effect();
private:
    int distortion_val;
};

#endif // EFFECTS_H
