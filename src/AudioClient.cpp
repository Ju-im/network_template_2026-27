#include "AudioClient.h"

void AudioClient::connect() {
	if(socket==nullptr){ socket = std::make_unique<sf::UdpSocket>(); }
	
	if (socket->bind(53001) != sf::Socket::Status::Done)
	{
		std::cout << "Client couldnt bind to port" << std::endl;
	}
	else {
		std::cout << "We binded" << std::endl;
		std::cout << socket->getLocalPort() << std::endl;
	}
	//socket.setBlocking(false);
}

void AudioClient::run() {
	
	std::size_t received;
	unsigned short r_port;
	std::optional<sf::IpAddress> sender;
	sf::Packet packet;
	
	while (running) {
		if (socket->receive(packet,sender, r_port) != sf::Socket::Status::Done)
		{
			// error...
			
			std::cerr << "Error" << std::endl;
			
		}
		for (int i = 0; i < 100;i++) {
			std::int16_t num;
			packet >> num;
			data[i] = num;
			std::cout << data[i] << std::endl;

		}
		running = false;
		std::cout<< " bytes from " << sender.value().toString() << " on port " << r_port << std::endl;
		
	
	}
	
	
	

	
	

}
