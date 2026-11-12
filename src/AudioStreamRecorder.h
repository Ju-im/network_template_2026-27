#pragma once
#include <SFML/Audio.hpp>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>
#include <mutex>

class AudioStreamRecorder:public sf::SoundRecorder
{
public:
	std::vector<std::int16_t>m_samples;
protected:
	  virtual bool onProcessSamples(const std::int16_t* samples, std::size_t sampleCount) override;
};
