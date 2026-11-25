#include "AudioStreamRecorder.h"



void AudioStreamRecorder::onStop()
{

    outgoing_queue.push(m_samples);
}

bool AudioStreamRecorder::onStart()
{
    setChannelCount(2);
    buffer.reserve(getSampleRate() * 0.03);
    return true;
}



bool AudioStreamRecorder::onProcessSamples(const std::int16_t* samples, std::size_t sampleCount)
{
   
    //20ms pass
    // std::int16_t s = *samples;
     //  std::copy(s, s + sampleCount, std::back_inserter(m_samples));
       //m_samples.emplace_back(samples);
    std::int16_t* cast = (std::int16_t*)samples;
  
   // std::vector< std::int16_t*, std::allocator<std::int16_t*>> temp = { { cast,alloc } };
    //need a buffer 44.1kh samples per second == 44.1k samples
    // we need 4kh samples per 0.03 seconds== 1323 samples 
   
    flat_samples.insert(flat_samples.end(), samples, samples + sampleCount);
    m_samples.push_back(cast);
    m_sampleCount.push_back(sampleCount);
    
   
    return true;
}
