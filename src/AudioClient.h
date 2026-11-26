#pragma once
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <atomic>
#include<iostream>
#include <thread>
#include "AudioStreamRecorder.h"

class AudioClient
{
public:
	void connect();
	void init();
	void run();
	void sendCheck();
	void play();
	std::atomic<bool> running = true;
	std::atomic<bool> connected = false;
	std::vector<std::int16_t> samples;
	std::unique_ptr<sf::UdpSocket> socket;
	int port = 54000;
	std::unique_ptr<sf::UdpSocket> check_socket;
	
	
	int size = 0;
	bool played = false;
private:
	bool recieved = false;
	std::size_t received;
	unsigned short r_port;
	std::optional<sf::IpAddress> sender;
	AudioStreamRecorder recorder;
};
