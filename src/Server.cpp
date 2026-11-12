#include "Server.h"






void Server::init() {


	if (listener == nullptr) {
		listener = std::make_unique < sf::TcpListener>();
	}
	if (listener->listen(port) != sf::Socket::Status::Done) {
		std::cout << "Couldnt bind listener to port " << port;
	}
}



void Server::run(){
	std::thread input_thread([&] {input(); });
	input_thread.detach();
	while (running) {

		sf::TcpSocket& c_sock = *connecetions.emplace_back(std::make_unique<sf::TcpSocket>());
		if (listener->accept(c_sock) != sf::Socket::Status::Done) {
			connecetions.pop_back();
			std::cout << "Connections failed on server side" << std::endl;
			continue;
		}
	std::cout << "Client connected @ " << c_sock.getRemotePort() << std::endl;

	workers.emplace_back([&] {
		listen(c_sock);
		std::cout << "Disconnect detected" << std::endl;
		std::lock_guard<std::mutex> lck(mutex);
		for (int i = 0; i < connecetions.size(); i++) {
			if (connecetions[i]->getRemotePort() == c_sock.getRemotePort()) {
				connecetions.erase(std::next(connecetions.begin(), i));
				break;
			}
		}
		});
	
	}

	
	
	
}

void Server::input() {
	while (running) {
		std::string str;
		std::getline(std::cin, str);
		std::cin.clear();
		std::lock_guard<std::mutex>lck(mutex);
		for (std::unique_ptr<sf::TcpSocket>& connection : connecetions) {
			connection->send(reinterpret_cast<char*>(str.data()), str.length());
		}
	}
	
}

void Server::listen(sf::TcpSocket& c_socket) {

	bool continue_recieveing = true;

	char data[1028];
	std::size_t recieved;
	std::cout << "Server something" << std::endl;
	while (continue_recieveing) {

		sf::Socket::Status status = c_socket.receive(data, 1028, recieved);

		if (status == sf::Socket::Status::Disconnected) {

			continue_recieveing = false;
			std::cout << "Disconnected" << std::endl;
		}
		if (recieved < 1028) { data[recieved] = '\0'; }
		relay(data, c_socket);
		
		std::cout << reinterpret_cast<char*>(data) << std::endl;
	}
	c_socket.disconnect();
}

void Server::relay(std::string buffer, sf::TcpSocket& c_socket) {
	char* message = reinterpret_cast<char*>(buffer.data());

	std::lock_guard<std::mutex> lck(mutex);
	for (std::unique_ptr<sf::TcpSocket>& connection : connecetions) {
		if (connection->getRemotePort() != c_socket.getRemotePort()) {
			std::cout << "sending messages to other clients" << std::endl;
			connection->send(message, buffer.size());
		}
	}
}
