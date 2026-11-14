#include "AudioStreamRecorder.h"



void AudioStreamRecorder::onStop()
{

    outgoing_queue.push(m_samples);
}



bool AudioStreamRecorder::onProcessSamples(const std::int16_t* samples, std::size_t sampleCount)
{
   
    //20ms pass
    // std::int16_t s = *samples;
     //  std::copy(s, s + sampleCount, std::back_inserter(m_samples));
       //m_samples.emplace_back(samples);
    std::int16_t* cast = (std::int16_t*)samples;
  
   // std::vector< std::int16_t*, std::allocator<std::int16_t*>> temp = { { cast,alloc } };
    
    m_samples.push_back(cast);
    m_sampleCount.push_back(sampleCount);
    
   
    return true;
}
