#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include <SFML/Audio.hpp>
#include <iostream>
#include<mutex>
#include <memory>
#include "AudioStreamRecorder.h"
class AudioServer
{
public:
	AudioServer(AudioStreamRecorder& m_recorder);
	void init(std::vector<std::int16_t>& data);


	void listen(sf::TcpSocket& u_socket);
	void relay(std::string buffer, sf::TcpSocket& u_socket);
	

	void input();
	bool onGetData(int samplesToStream);
	std::atomic<bool> recordingFinished = false;
	std::size_t m_current_sample{};
	std::vector<std::int16_t> samples;
	private:
		AudioStreamRecorder& recorder;
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
	bool finished_sending = false;



	enum class PacketType : std::uint8_t {
		AUDIO =0,
		END=1
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
