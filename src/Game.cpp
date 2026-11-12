#include "Game.h"
#include "Tile.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  
}

Game::~Game()
{
    
}

bool Game::init()
{
    board = std::make_shared<Board>(window);
    board->init();   
   
    audio_stream.init();
    host_text.setString("Host Game");
    host_text.setCharacterSize(50);
    host_text.setPosition({ 900.f,300.f });

    

    join_text.setString("Join Game");
    join_text.setCharacterSize(50);
    join_text.setPosition({ 900.f,400.f });
    return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
    window.draw(host_text);
    window.draw(join_text);
    board->render();    
}

void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
  
    const sf::Vector2f mousePos =
        window.mapPixelToCoords(event->position);
    if (gs == MENU) {
        if (host_text.getGlobalBounds().contains(mousePos))
        {
            gs = PLAY;
            std::cout << "Creating server" << std::endl;
            server = std::make_unique<Server>();
            
            //
            //std::thread input_thread([&] {server; });
            server->init();
           
            server_thread = std::thread([&] { server->run(); });
            server_thread.detach();
        }
        else if (join_text.getGlobalBounds().contains(mousePos)) {
            gs = PLAY;
            std::cout << "Attempting to connect to Server" << std::endl;
            client = std::make_unique<Client>();
            client->connect();
            client_thread = std::thread([&] { client->run(); });
          
            client_thread.detach();
            
           

        }
   }
   
    board->mouseButtonPressed(event);
}

void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
    board->mouseButtonReleased(event);    

}

void Game::keyPressed(const sf::Event::KeyPressed* event)
{

}

void Game::keyReleased(const sf::Event::KeyReleased* event)
{

}

void Game::mouseMoved(const sf::Event::MouseMoved* event)
{
    board->mouseMoved(event);
}







