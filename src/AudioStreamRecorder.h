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
	bool getNextChunk(std::vector<std::int16_t>& chunk);

	std::queue<std::vector<std::int16_t>> m_samples;
	std::vector<std::size_t> m_sampleCount;
	std::vector<std::int16_t>flat_samples;
	bool push_to_talk = true;
	std::mutex m_mutex;




	void onStop() override;
	bool onStart() override;
protected:
	  virtual bool onProcessSamples(const std::int16_t* samples, std::size_t sampleCount) override;
};
