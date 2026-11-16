#pragma once
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <atomic>
#include<iostream>
#include <thread>
class AudioClient
{
public:
	void connect();
	void init();
	void run();
	std::atomic<bool> running = true;
	std::atomic<bool> connected = false;
	std::array<std::int16_t, 100> data;
	std::unique_ptr<sf::UdpSocket> socket;
	int port = 54000;

private:
	
};
