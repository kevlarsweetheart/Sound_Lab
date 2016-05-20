#include "effects.h"

using namespace Effects;

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::set_amps(std::vector<int> amps)
{
    this->amplitudes = amps;
}

std::vector<int> Effect::get_amps()
{
    return this->amplitudes;
}

void Effect::apply_effect()
{
}
