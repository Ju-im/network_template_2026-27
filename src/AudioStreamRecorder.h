#pragma once
#include <SFML/Audio.hpp>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>
#include <mutex>
#include <queue>

class AudioStreamRecorder:public sf::SoundRecorder
{
public:
	std::vector<std::int16_t*>m_samples;
	std::vector<std::size_t> m_sampleCount;

	bool push_to_talk = true;

	std::queue<std::vector<std::int16_t*>> outgoing_queue;




	void onStop() override;
	
protected:
	  virtual bool onProcessSamples(const std::int16_t* samples, std::size_t sampleCount) override;
};
