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

void AudioServer::run() {

	char result = rCheck();
	if (result == 'y') {
		std::cout << "Finished" << std::endl;
	}
}
void AudioServer::input() {
	
	/*std::thread run_thread([this] {run(); });
	run_thread.detach();*/
	std::cout << "In running" << std::endl;
	while(running){
		std::vector<std::int16_t> half_data;
		std::lock_guard<std::mutex>lck(mutex);
		const int samplesToStream = 100;
		
		
		if (!onGetData(samplesToStream)) {
			return;
		}

		sf::Packet packet;

		packet << PacketType::AUDIO;

		for (std::int16_t sample : data.chunk_frame) {
			packet << sample;
		}
		if (u_socket.send(packet, sf::IpAddress::Broadcast, 53001) != sf::Socket::Status::Done)
		{
			// error...
			
			
			

		}
		else {
			
			//std::cout << "Couldnt send" << std::endl;
			std::cout << "Sent the data" << std::endl;
			//data.samples = {};
			running = false;
			


		}
		running = true;
		data.chunk_frame.clear();
	}
	
	
}

bool AudioServer::onGetData(int samplesToStream)
{
	data.samples = new std::int16_t();

	if (m_current_sample + samplesToStream <= samples.size())
	{
		std::cout << "End not reached yet" << std::endl;
		// end not reached: stream the samples and continue
		for (int i = 0; i < samplesToStream;i++) {
			std::int16_t d =samples[m_current_sample + i];
			data.chunk_frame.push_back(d);
			
		}
		data.sampleCount = samplesToStream;
		m_current_sample += samplesToStream;
		return true;
		

	}
	else
	{
		std::cout << "End has been reached" << std::endl;
		data.sampleCount = samples.size() - m_current_sample;
		m_current_sample = samples.size();
		for (int i = 0; i < data.sampleCount; i++) {
			std::int16_t d = samples[samplesToStream+ i];
			data.chunk_frame.push_back(d);

		}
		
		// end of stream reached: stream the remaining samples and stop playback
		if (u_socket.send(data.chunk_frame.data(), samplesToStream, sf::IpAddress::Broadcast, 53001) != sf::Socket::Status::Done)
		{
			// error...




		}
		else {

			//std::cout << "Couldnt send" << std::endl;
			std::cout << "Sent the data" << std::endl;
			//data.samples = {};
			sf::Packet packet;
			packet << PacketType::END;

			u_socket.send(packet, sf::IpAddress::Broadcast, 53001);
			std::cout << "END Packet sent" << std::endl;


		}
		
		/*std::thread check_thread([this] {rCheck(); });
		check_thread.detach();*/
		
		return false;
	}
}


char AudioServer::rCheck() {
	char str[1];
	std::size_t received;
	unsigned short r_port;
	std::optional<sf::IpAddress> sender;
	std::cout << "In rCheck" << std::endl;

		if (check_socket.receive(str, 1, received, sender, r_port) != sf::Socket::Status::Done) {
			//error

			std::cout << "Error in AS rCheck" << std::endl;
		}
		
		if (str[0] == 'y') {
		
			return 'y';
			
		}

		
	
	
	
}


