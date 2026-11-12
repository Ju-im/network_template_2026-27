#include "AudioStream.h"

AudioStream::AudioStream()
{
	//
}

AudioStream::~AudioStream()
{
	//
}

int AudioStream::init()
{
	if (!sf::SoundBufferRecorder::isAvailable()) {
		std::cerr << "Microphone access is not available on this system.\n";
		return 1;
	}
	std::cout << "Available input devices:\n";
	for (const auto& device : sf::SoundRecorder::getAvailableDevices()) {
		std::cout << " - " << device << "\n";
	}
	//recorder.setDevice("DeviceName");
	
	sample_rate = recorder.getSampleRate();
	channel = recorder.getChannelCount();
	
	std::cout << "Sample rate: " << sample_rate << "Channel(s): " << channel << "Default Device(0): "<< recorder.getDefaultDevice() << std::endl;
	
	return 0;
}

void AudioStream::getUserAudio()
{
	
	const sf::SoundBuffer& buffer = recorder.getBuffer();
}

void AudioStream::load(const sf::SoundBuffer& buffer)
{
	m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());
	m_current_sample = 0;
	initialize(buffer.getChannelCount(), buffer.getSampleRate(), { sf::SoundChannel::FrontLeft,sf::SoundChannel::FrontRight });

}

bool AudioStream::onGetData(Chunk& data)
{
	const int samplesToStream = 50000;
	data.samples = &m_samples[m_current_sample];
	if (m_current_sample + samplesToStream <= m_samples.size())
	{
		// end not reached: stream the samples and continue
		data.sampleCount = samplesToStream;
		m_current_sample += samplesToStream;
		return true;
	}
	else
	{
		// end of stream reached: stream the remaining samples and stop playback
		data.sampleCount = m_samples.size() - m_current_sample;
		m_current_sample = m_samples.size();
		return false;
	}
}

void AudioStream::onSeek(sf::Time timeOffset)
{
}


