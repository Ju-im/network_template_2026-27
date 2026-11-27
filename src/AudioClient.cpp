#include "AudioClient.h"

void AudioClient::connect() {
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
		std::array<std::int16_t, 100> buffer;
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
void AudioClient::play() {
		buffer.loadFromSamples(samples.data(), samples.size(), 2, 44100, recorder.getChannelMap());
		sound = new sf::Sound(buffer);
		
		
		
		sound->play();

	
		played = true;

	}
	


void AudioClient::sendCheck() {
	
	std::string str;
	sf::IpAddress receiver(sender.value());
	
		if (recieved) {
			str = 'y';
			std::cout << "Sending Check and we did recieve it " << std::endl;
			check_socket->send(reinterpret_cast<char*>(str.data()), str.length(), sf::IpAddress::Broadcast, 53003);
		}
	
	
	

}