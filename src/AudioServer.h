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
	void send(std::int16_t* sound, sf::TcpSocket& u_socket);

	void input();
	std::array<std::int16_t, 100> half_data;

	private:
		sf::Packet packet;
		sf::UdpSocket u_socket;
	std::vector<std::thread> workers;
	std::vector<std::unique_ptr<sf::UdpSocket>>connecetions;
	
	std::unique_ptr<sf::TcpListener> listener;
	int port = 53000;
	bool running = true;
	std::mutex mutex;
};
