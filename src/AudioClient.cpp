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

				std::int16_t sample;

				while (packet >> sample)
				{
					samples.push_back(sample);
				}
				std::cout << "Sample size: " << samples.size() <<std::endl;
			}
			else if (type == PacketType::END) {
				// Play the completed recording
				
				play();
			
			}
		}
		sf::sleep(sf::milliseconds(1));
	}
		



}
void AudioClient::play()
{
	std::cout << "1. Starting playback function\n";

	std::cout << "2. Loading buffer\n";

	if (!buffer.loadFromSamples(
		samples.data(),
		samples.size(),
		2,
		44100,
		recorder.getChannelMap()))
	{
		std::cout << "Failed to load audio\n";
		return;
	}

	std::cout << "3. Buffer loaded\n";

	sound = new sf::Sound(buffer);

	std::cout << "4. Sound created\n";

	sound->play();

	std::cout << "5. Playback started\n";
}


