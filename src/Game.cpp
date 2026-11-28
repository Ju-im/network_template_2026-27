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
   
   // audio_stream.init();
    recorder.start(44100);

    //sf::sleep(sf::seconds(2));
   
    //recorder.stop();


   
       
       
    

            
      
     
          
        
     
    
    
    host_text.setString("Host Game");
    host_text.setCharacterSize(50);
    host_text.setPosition({ 900.f,300.f });

    

    join_text.setString("Join Game");
    join_text.setCharacterSize(50);
    join_text.setPosition({ 900.f,400.f });

    send_text.setString("Send");
    send_text.setCharacterSize(50);
    send_text.setPosition({ 900.f,500.f });
    return true;
}

void Game::update(float dt)
{
    if (connected && !as_started) {
        as = std::make_unique<AudioServer>(recorder);
        as->init(recorder.flat_samples);

        server_thread = std::thread([&] {   as->input(); });
        server_thread.detach();
        as_started = true;

    }
}

void Game::render()
{
    window.draw(host_text);
    window.draw(join_text);
    board->render();    
    window.draw(send_text);
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
           
            tcp_server_thread = std::thread([&] { server->run(connected); });
            tcp_server_thread.detach();
           
          
          
        }
        else if (join_text.getGlobalBounds().contains(mousePos)) {
            gs = PLAY;
           
     
            std::cout << "Attempting to connect to Server" << std::endl;
            client = std::make_unique<Client>();
            client->connect();
           
            tcp_client_thread = std::thread([&] { client->run(); });
          
            tcp_client_thread.detach();


            ac = std::make_unique<AudioClient>();
            ac->connect();
            ac->size = recorder.flat_samples.size();
           
        
            client_thread = std::thread([&] { ac->run(); });
            client_thread.detach();
            std::vector<std::int16_t> chunk;

            if (recorder.getNextChunk(chunk))
            {
                std::cout << "Retrieved: " << chunk.size() << " samples\n";
            }
      


          
          
        
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
    if (event->scancode == sf::Keyboard::Scancode::W)
    {
        as->recordingFinished = true;
    }

}

void Game::mouseMoved(const sf::Event::MouseMoved* event)
{
    board->mouseMoved(event);
}



