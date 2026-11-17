#include "AudioServer.h"

void AudioServer::init(std::vector<std::int16_t>& data) {


	if (u_socket.bind(53000) != sf::Socket::Status::Done) {
		std::cout << "Error";
	}
	else {
		std::cout << "We binded" << std::endl;
		std::cout <<"Server Port: "<< u_socket.getLocalPort() << std::endl;
	}
	
	
	int j = 0;
	for (int i = 0; i < data.size(); i++) {
		if (abs(data[i]) < 30) {
			continue;
		}
		if (j < 100) {
			half_data[j] = data[i];
			j++;


		}
		if (j >= 100) {
			std::cout << "Done" << std::endl;
			break;
		}
	}

	for (auto data : half_data) {
		std::cout << "Data" << data << std::endl;
	}
}


void AudioServer::input() {
	
	while(running){
		//std::lock_guard<std::mutex>lck(mutex);

		sf::Packet packet;
		packet << static_cast<std::uint32_t>(half_data.size());

		// Send each element
		for (std::int16_t num : half_data) {
			packet << num;
		}
		if (u_socket.send(half_data.data(), half_data.size(), sf::IpAddress::Broadcast, 53001) != sf::Socket::Status::Done)
		{
			// error...
			
			
			

		}
		else {
			
			//std::cout << "Couldnt send" << std::endl;
			std::cout << "Sent the data" << std::endl;
		}
	}
	

}





