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
	void play(const std::vector<std::int16_t>& samples);


	std::atomic<bool> running = true;
	std::atomic<bool> connected = false;

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
	sf::SoundBuffer buffer;
	std::unique_ptr<sf::Sound> sound;
	enum class PacketType : std::uint8_t {
		AUDIO,
		END
	};



	friend sf::Packet& operator<<(sf::Packet& packet, const PacketType& type)
	{
		return packet << static_cast<std::uint8_t>(type);
	}

	friend sf::Packet& operator>>(sf::Packet& packet, PacketType& type)
	{
		std::uint8_t value;
		packet >> value;
		type = static_cast<PacketType>(value);
		return packet;
	}
};
