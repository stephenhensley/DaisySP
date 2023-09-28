#include "dsp.h"
#include "limiter.h"

#define SLOPE(out, in, positive, negative)                \
    {                                                     \
        float error = (in)-out;                           \
        out += (error > 0 ? positive : negative) * error; \
    }

namespace daisysp
{
void Limiter::Init()
{
    peak_ = 0.5f;
}

void Limiter::ProcessBlock(float *in, size_t size, float pre_gain)
{
    while(size--)
    {
        float pre  = *in * pre_gain;
        float s = pre;
        SLOPE(peak_, fabsf(s), 0.05f, 0.00002f);
        float gain = (peak_ <= 1.0f ? 1.0f : 1.0f / peak_);
        *in++ = s * gain * 0.8f;
        // *in++      = SoftLimit(pre * gain * 0.7f);
    }
}

} //namespace daisysp