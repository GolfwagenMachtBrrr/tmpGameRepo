#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


#include "MapGenerator.h"
#include "NoizeGenerator.h"
#include "Player.h"
#include "Gun.h"
#include "TextureHolder.h"
#include "Inventory.h"
#include "EnemyManager.h"

#include <iostream>
#include <random>


class GameWindow
{
public:

    void Start(bool start)
    {
        if (start)
        {
            this->InitEnemyManager();
            this->InitWindow();
            this->InitPlayer(); 
            this->IntitOtherValues();
            this->InitMap();
            this->InitViewer();
            this->GameLoop();
        }
    }

    void InitEnemyManager()
    {
        sf::Vector2f center(this->m_player.GetPosition());
        this->m_enemymanager.Initialize(center);

    }

    void IntitOtherValues()
    {
        this->m_tilesheet = "../Assets/World/NumsVer3.png";
        this->m_tilesize.x = 25;
        this->m_tilesize.y = 40;
        this->m_dt = 16;

        // Mouse logic
        m_curor_texture = m_textures.GetTexture("cursor"); 
        this->m_cursor.setTexture(m_curor_texture);

        //Inventory
        
    }

    void InitWindow()
    {
        this->m_window.create(sf::VideoMode(1920, 1080), "GameWindow");
        this->m_window.setMouseCursorVisible(false);
    }

    void InitMap()
    {
        int width = m_window.getSize().x / m_tilesize.x; std::cout << width << std::endl;
        int height = m_window.getSize().y / m_tilesize.y; std::cout << height << std::endl; 

        this->m_inventory.Initialize(m_textures, m_window.getSize().x, m_window.getSize().y);

        this->m_map.Initialize(m_tilesize, m_tilesheet, width, height);
        this->m_map.Generate();
    }

    void InitViewer()
    {
        sf::Vector2f startingPosition(0, 0);
        float speed = 0.125 / 20;
        float zoom = 0.2;

        this->m_gameview.Initialize(startingPosition, speed, zoom);
    }

    void InitPlayer()
    {
        this->m_player.Initalize(m_textures);
       
       
    }
    
    int GameLoop()
    {
        while (m_window.isOpen())
        {
            // Calculate DeltaTime
            m_dt = 16;

            // Process events
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            sf::Vector2f cursorPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
            sf::Vector2f worldPos = m_window.mapPixelToCoords(static_cast<sf::Vector2i>(cursorPosition));
            sf::Vector2f tmp = m_window.mapPixelToCoords(static_cast<sf::Vector2i>(cursorPosition), m_inventory.p_view);


            m_cursor.setPosition(worldPos);

            m_window.clear();

            m_playergun.Update(m_dt, m_player.GetPosition(), cursorPosition);
            m_player.Update(m_dt, m_window); 
 
            m_inventory.Update(tmp);
            m_gameview.Update(m_dt);

            this->m_enemymanager.Update(this->m_dt, this->m_player.GetPosition(), this->m_player.GetHitBox());

            m_gameview.setViewCenter(m_player.GetPosition());
            m_window.setView(m_gameview.GetView());

     
            m_map.Draw(m_window, m_gameview);
            m_player.Draw(m_window); 
            m_playergun.Draw(m_window);

            this->m_enemymanager.Draw(this->m_window);

            m_window.draw(m_cursor);
            m_window.setView(m_inventory.p_view);
           
   
            m_window.draw(m_cursor);

            m_inventory.Draw(m_window);
           
     
            m_window.display();
        }

        return EXIT_SUCCESS;
    }


private:
    sf::RenderWindow m_window;

    std::string m_tilesheet;
    sf::Vector2u m_tilesize;

    MapGenerator m_map;
    Viewer m_gameview;
    Inventory m_inventory; 

    Player m_player; 
    Gun m_playergun; 

    EnemieManager m_enemymanager; 

    TextureHolder m_textures;

    sf::Texture m_curor_texture; 
    sf::Sprite m_cursor; 

    float m_dt;
};

