#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include<mutex>
#include <memory>
#include <iostream>

class AudioStream: public sf::SoundStream
{
public:
	AudioStream();
	~AudioStream();
	int init();
	bool onGetData(Chunk& data) override;
	void onSeek(sf::Time timeOffset) override;
	void getUserAudio();
	void load(const sf::SoundBuffer& buffer);
private:
	sf::SoundBufferRecorder recorder;
	std::vector<std::int16_t>m_samples;
	std::size_t m_current_sample{};
	std::mutex mutex;
	unsigned int sample_rate;
	unsigned int channel;
};
