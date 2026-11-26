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


	//socket.setBlocking(false);
}



void AudioClient::run() {
	
	
	
	std::cout << "In Client running state" << std::endl;
	std::array<std::int16_t, 100> buffer;

	while(running){
		if (socket->receive(buffer.data(), buffer.size(), received, sender, r_port) != sf::Socket::Status::Done)
		{
			// error...


			recieved = false;


			
		}
		else {
			std::cout << " bytes from " << sender.value().toString() << " on port " << r_port << "Recieved: " << received << std::endl;
			recieved = true;


			samples.insert(samples.end(), buffer.begin(), buffer.end());
			std::cout << "Current sample size: " << samples.size();
			//sendCheck();
			play();
		}
	}
		



}
void AudioClient::play() {

	if (samples.size() >= size*0.8 && !played) {
		sf::SoundBuffer buffer;
		buffer.loadFromSamples(samples.data(), samples.size(), 2, 44100, recorder.getChannelMap());
		sf::Sound sound(buffer);
		sound.play();

		while (sound.getStatus() == sf::Sound::Status::Playing) {
			std::cout << "Time offset: " << sound.getPlayingOffset().asSeconds() << std::endl;
			sf::sleep(sf::milliseconds(100));

		}
		played = true;

	}
	else {
		std::cout << "Not big enough" << std::endl;
	}
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