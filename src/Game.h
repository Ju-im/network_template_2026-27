
#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Server.h"
#include "Client.h"
#include"AudioStream.h"
#include "AudioStreamRecorder.h"


class Game
{
 public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
	void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
	void keyPressed(const sf::Event::KeyPressed* event);
	void keyReleased(const sf::Event::KeyReleased* event);
	void mouseMoved(const sf::Event::MouseMoved* event);
	enum GameState 
	{
		MENU,
		PLAY,
		PAUSE


	};
	GameState gs = MENU;
 private:
	sf::RenderWindow& window;
	sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };
	sf::Text host_text{ font };
	sf::Text join_text{ font };
	std::shared_ptr<Board> board;
	std::unique_ptr<Server> server;
	std::unique_ptr<Client> client;
	std::thread server_thread;
	std::thread client_thread;
	AudioStream audio_stream;
	AudioStreamRecorder recorder;
	sf::SoundBuffer buffer;
};

