#include "effects.h"

using namespace Effects;

Distortion::Distortion()
{
}

void Distortion::set_distort_val(int value)
{
    this->distortion_val = value;
}

int Distortion::get_distort_val()
{
    return this->distortion_val;
}

void Distortion::apply_effect()
{
    int len = amplitudes.size();
    for (int i = 0; i < len; ++i)
    {
        if (amplitudes[i] > distortion_val)
            amplitudes[i] = distortion_val;
        else if (amplitudes[i] < -distortion_val)
            amplitudes[i] = -distortion_val;
    }
}
