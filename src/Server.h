#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <vector>

#include <iostream>
#include<mutex>
#include <memory>
class Server
{
public:
	void init();
	void run();
	void listen(sf::TcpSocket& c_socket);
	void relay(std::string buffer, sf::TcpSocket& c_socket);
	void send(std::string buffer, sf::TcpSocket& c_socket);

	void input();
	


private:
	std::vector<std::thread> workers;
	std::vector<std::unique_ptr<sf::TcpSocket>>connecetions;

	std::unique_ptr<sf::TcpListener> listener;
	int port = 53000;
	bool running = true;
	std::mutex mutex;
};
