#include "AudioServer.h"

void AudioServer::init(std::vector<std::int16_t>& m_data) {

	if (u_socket.bind(53000) != sf::Socket::Status::Done) {
		std::cout << "Error";
	}
	else {
	//
	}

	if (check_socket.bind(53003) != sf::Socket::Status::Done) {
		std::cout << "Error";
	}
	else {
		//
	}
	
	
	for (std::int16_t samp : m_data) {
		samples.push_back(samp);
	}
	


	m_current_sample = 0;
	

}




void AudioServer::input()
{
	std::cout << "In running" << std::endl;

	std::lock_guard<std::mutex> lck(mutex);

	const int samplesToStream = 1764;

	while (running)
	{
		// Prepare the next chunk
		if (!onGetData(samplesToStream))
		{
			// No samples left: tell the client transmission has finished
			sf::Packet packet;
			packet << PacketType::END;

			if (u_socket.send(packet, sf::IpAddress::Broadcast, 53001)
				!= sf::Socket::Status::Done)
			{
				std::cout << "Failed to send END packet" << std::endl;
			}
			else
			{
				std::cout << "END Packet sent" << std::endl;
			}

			running = false;
			break;
		}

		// Send the prepared audio chunk
		sf::Packet packet;
		packet << PacketType::AUDIO;

		for (std::int16_t sample : data.chunk_frame)
		{
			packet << sample;
		}

		if (u_socket.send(packet, sf::IpAddress::Broadcast, 53001)
			!= sf::Socket::Status::Done)
		{
			std::cout << "Failed to send audio packet" << std::endl;
			running = false;
			break;
		}

		std::cout << "Sent " << data.sampleCount << " samples" << std::endl;
		sf::sleep(sf::milliseconds(20));
	}
}

bool AudioServer::onGetData(int samplesToStream)
{
	// Clear the previous chunk
	data.chunk_frame.clear();

	// Check whether we have reached the end
	if (m_current_sample >= samples.size())
	{
		return false;
	}

	// Calculate how many samples remain
	int remaining = samples.size() - m_current_sample;

	// Take either 100 samples or whatever remains
	int samplesToCopy = std::min(samplesToStream, remaining);

	for (int i = 0; i < samplesToCopy; i++)
	{
		std::int16_t d = samples[m_current_sample + i];
		data.chunk_frame.push_back(d);
	}

	data.sampleCount = samplesToCopy;

	// Move our position forward
	m_current_sample += samplesToCopy;

	return true;
}



