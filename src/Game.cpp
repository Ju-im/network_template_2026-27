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
    recorder.start();

    sf::sleep(sf::seconds(1));
   
    recorder.stop();

    
  
    std::vector<std::int16_t*> samples = recorder.outgoing_queue.front();
    //std::vector<std::int16_t*> samples;
    
    sf::SoundBuffer m_buffer;
    std::vector<std::int16_t> flatSample;
  
   
       
       
    
        

        m_buffer.loadFromSamples(recorder.flat_samples.data(), recorder.flat_samples.size(), recorder.getChannelCount(), 44100, recorder.getChannelMap());
            std::cout << "Duration: " << m_buffer.getDuration().asSeconds() << std::endl;
            buffer = m_buffer;
            sf::Sound sound(buffer);
            
        
           // sound.setLooping(true);
     
            sound.play();
            while (sound.getStatus() == sf::Sound::Status::Playing) {
                std::cout <<"Time offset: " << sound.getPlayingOffset().asSeconds() << std::endl;
                sf::sleep(sf::milliseconds(100));
               
            }
        
     
    
    
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
           /* server = std::make_unique<Server>();
            
            //
            //std::thread input_thread([&] {server; });
            server->init();
           
            server_thread = std::thread([&] { server->run(); });
            server_thread.detach();*/
            as = std::make_unique<AudioServer>();
            as->init(recorder.flat_samples);
          
            server_thread = std::thread([&] {   as->input(); });
            server_thread.detach();
            
          
        }
        else if (join_text.getGlobalBounds().contains(mousePos)) {
            gs = PLAY;
            std::cout << "Attempting to connect to Server" << std::endl;
           /* client = std::make_unique<Client>();
            client->connect();
            client_thread = std::thread([&] { client->run(); });
          
            client_thread.detach();*/
            ac = std::make_unique<AudioClient>();
            ac->connect();
           
            
            client_thread = std::thread([&] { ac->run(data); });
            client_thread.detach();
            std::array<std::int16_t,100>
            sf::SoundBuffer sound_buffer;
            sound_buffer.loadFromSamples(data.data(), data.size(), recorder.getChannelCount(), 44100, recorder.getChannelMap());
            sf::Sound sound (sound_buffer);
            sound.play();
            std::cout << "Duration: " << sound_buffer.getDuration().asSeconds() << std::endl;
            while (sound.getStatus() == sf::Sound::Status::Playing) {
                sf::sleep(sf::milliseconds(100));
                std::cout << sound.getPlayingOffset().asSeconds() << std::endl;
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

}

void Game::mouseMoved(const sf::Event::MouseMoved* event)
{
    board->mouseMoved(event);
}







