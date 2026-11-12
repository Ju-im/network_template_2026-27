#include "AudioStreamRecorder.h"

bool AudioStreamRecorder::onProcessSamples(const std::int16_t* samples, std::size_t sampleCount)
{
    std::copy(samples, samples + sampleCount, std::back_inserter(m_samples));
    return false;
}
