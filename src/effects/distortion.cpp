#include "effects.h"

Distortion::Distortion() : Effect::Effect()
{
    this->type = DISTORTION;
}

void Distortion::set_distort_val(int value)
{
    this->distortion_val = value;
}

int Distortion::get_distort_val()
{
    return this->distortion_val;
}

std::vector<int> Distortion::apply_effect(std::vector<int> amplitudes)
{
    int len = amplitudes.size();
    for (int i = 0; i < len; ++i)
    {
        if (amplitudes[i] > distortion_val)
            amplitudes[i] = distortion_val;
        else if (amplitudes[i] < -distortion_val)
            amplitudes[i] = -distortion_val;
    }
    return amplitudes;
}
