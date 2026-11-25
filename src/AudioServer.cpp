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
	for (int i = 0; i < 101; i++) {
		samples[i] = 100-i;
	}


	m_current_sample = 0;
	

}


void AudioServer::input() {
	int i = 0;
	while(running){
		std::vector<std::int16_t> half_data;
		std::lock_guard<std::mutex>lck(mutex);
		const int samplesToStream = 100;
		
		if (!onGetData(samplesToStream)) {
			return;
		}

		
		if (u_socket.send(data.chunk_frame.data(), data.chunk_frame.size(), sf::IpAddress::Broadcast, 53001) != sf::Socket::Status::Done)
		{
			// error...
			
			
			

		}
		else {
			
			//std::cout << "Couldnt send" << std::endl;
			std::cout << "Sent the data" << std::endl;
			//data.samples = {};
			rCheck();

		}
	}
	

}

bool AudioServer::onGetData(int samplesToStream)
{
	data.samples = new std::int16_t();

	if (m_current_sample + samplesToStream <= samples.size())
	{
		// end not reached: stream the samples and continue
		for (int i = 0; i < samplesToStream;i++) {
			std::int16_t d =samples[m_current_sample];
			data.chunk_frame.push_back(d);
			
		}
		data.sampleCount = samplesToStream;
		m_current_sample += samplesToStream;
		return true;
		

	}
	else
	{
		data.sampleCount = samples.size() - m_current_sample;
		m_current_sample = samples.size();
		for (int i = 0; i < data.sampleCount; i++) {
			std::int16_t d = samples[i];
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


		}
		
		return false;
	}
}


void AudioServer::rCheck() {
	char str[1];
	std::size_t received;
	unsigned short r_port;
	std::optional<sf::IpAddress> sender;

	if (u_socket.receive(str, 1, received, sender, r_port) != sf::Socket::Status::Done) {
		//error
		std::cout << "Error" << std::endl;
	}
	std::cout << "Check Answer: " << str[0] << std::endl;
	if (str[0] == 'y') {
		running = true;
	}
	else {
		running = false;
	}
}


