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


//void modifyMessage(std::promise<std::string>&& prms, std::string message)
//{
//	std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // simulate work
//	std::string modifiedMessage = message + " has been modified";
//	prms.set_value(modifiedMessage);
//}
void AudioClient::run(std::promise<std::array<std::int16_t,100>>&&prms, std::array<std::int16_t, 100>& game) {
	
	
	
	
	
		
		if (socket->receive(game.data(), game.size(),received,sender ,r_port) != sf::Socket::Status::Done)
		{
			// error...
			
			std::cerr << "Error" << std::endl;
			recieved = false;
		
			
			
		}
		else {
			std::cout << " bytes from " << sender.value().toString() << " on port " << r_port << "Recieved: " << received << std::endl;
			recieved = true;

			prms.set_value(game);
			//sendCheck();
		}



}


void AudioClient::sendCheck() {
	/*if (!sender.has_value() || r_port) {
		return;
	}*/
	std::string str;
	sf::IpAddress receiver(sender.value());
	if (recieved) {
		str = 'y';
		socket->send(reinterpret_cast<char*>(str.data()), str.length(), sf::IpAddress::Broadcast, 53003);
	}
	else {
		str = 'n';
		socket->send(reinterpret_cast<char*>(str.data()), str.length(), sf::IpAddress::Broadcast, 53003);
	}

}