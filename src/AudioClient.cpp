#include "AudioClient.h"

void AudioClient::connect() {
	recorder.setChannelCount(2);
	if(socket==nullptr){ socket = std::make_unique<sf::UdpSocket>(); }
	if (check_socket == nullptr) { check_socket = std::make_unique<sf::UdpSocket>(); }
	
	if (socket->bind(53001) != sf::Socket::Status::Done)
	{
		std::cout << "Client couldnt bind to port" << std::endl;
	}
	else {
		std::cout << "We binded" << std::endl;
		std::cout << socket->getLocalPort() << std::endl;
	}


	if (check_socket->bind(53002) != sf::Socket::Status::Done)
	{
		std::cout << "Client couldnt bind to port" << std::endl;
	}
	else {
		std::cout << "We binded" << std::endl;
		std::cout << check_socket->getLocalPort() << std::endl;
	}
	socket->setBlocking(false);

}



void AudioClient::run() {
	
	
	
	std::cout << "In Client running state" << std::endl;
	


	while(running){
	

		sf::Packet packet;

		if (socket->receive(packet, sender, r_port)
			== sf::Socket::Status::Done) {

			PacketType type;
			packet >> type;

			if (type == PacketType::AUDIO) {
				// Extract audio samples

				std::vector<std::int16_t> samples;

				std::int16_t sample;

				while (packet >> sample)
				{
					samples.push_back(sample);
				}
				std::cout << "Sample size: " << samples.size() <<std::endl;
				play(samples);
			}
			else if (type == PacketType::END) {
				// Play the completed recording
				recorder.stop();
				std::cout << "Finished transmission" << std::endl;
			
			}
		}
		sf::sleep(sf::milliseconds(1));
	}
		



}
void AudioClient::play(const std::vector<std::int16_t>& samples)
{
	buffer.loadFromSamples(
		samples.data(),
		samples.size(),
		2,
		44100,recorder.getChannelMap()
	);

	sound = std::make_unique<sf::Sound>(buffer);
	sound->play();
}


