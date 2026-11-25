#pragma once
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <atomic>
#include<iostream>
#include <thread>
#include <future>

class AudioClient
{
public:
	void connect();
	void init();
	void run(std::promise<std::array<std::int16_t, 100>>&& prms,std::array<std::int16_t,100> &game);
	void sendCheck();
	std::atomic<bool> running = true;
	std::atomic<bool> connected = false;
	std::array<std::int16_t, 100> data;
	std::unique_ptr<sf::UdpSocket> socket;
	int port = 54000;
	std::unique_ptr<sf::UdpSocket> check_socket;
	
	

private:
	bool recieved = false;
	std::size_t received;
	unsigned short r_port;
	std::optional<sf::IpAddress> sender;
};
