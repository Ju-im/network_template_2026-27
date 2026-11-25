#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include <SFML/Audio.hpp>
#include <iostream>
#include<mutex>
#include <memory>
class AudioServer
{
public:
	void init(std::vector<std::int16_t>& data);
	void run(const std::int16_t sound);

	void listen(sf::TcpSocket& u_socket);
	void relay(std::string buffer, sf::TcpSocket& u_socket);
	

	void input();
	bool onGetData(int samplesToStream);
	void rCheck();
	std::size_t m_current_sample{};
	std::vector<std::int16_t> samples;
	private:
		sf::UdpSocket check_socket;
		sf::UdpSocket u_socket;
	std::vector<std::thread> workers;
	std::vector<std::unique_ptr<sf::UdpSocket>>connecetions;
	struct Chunk
	{
		const std::int16_t* samples{};     //!< Pointer to the audio samples
		std::size_t         sampleCount{};//!< Number of samples pointed by Samples
		std::vector<std::int16_t> chunk_frame;
	};
	Chunk data;
	std::unique_ptr<sf::TcpListener> listener;
	int port = 53000;
	bool running = true;
	std::mutex mutex;
};
