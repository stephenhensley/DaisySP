#include <math.h>
#include "phasor.h"
#include "dsp.h"

using namespace daisysp;

static constexpr float kTwoPiRecip = 1.f / TWOPI_F;


void Phasor::Init(float sample_rate, float freq, float initial_phase)
{
    sample_rate_     = sample_rate;
    phs_             = initial_phase;
    two_pi_recip_sr_ = TWOPI_F * (1.f / sample_rate_);
    SetFreq(freq);
}


void Phasor::SetFreq(float freq)
{
    freq_ = freq;
    //inc_  = (TWOPI_F * freq_) / sample_rate_;
    inc_ = two_pi_recip_sr_ * freq_;
}

float Phasor::Process()
{
    float out;
    // out = phs_ / TWOPI_F;
    out = phs_ * kTwoPiRecip;
    phs_ += inc_;
    if(phs_ > TWOPI_F)
    {
        phs_ -= TWOPI_F;
    }
    if(phs_ < 0.0f)
    {
        phs_ += TWOPI_F;
    }
    return out;
}
