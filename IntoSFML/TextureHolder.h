#pragma once

#include "SFML/Graphics.hpp"
#include <map>
#include <string>
#include <iostream>
#include <string>


struct TextureHolder
{
public:
	std::string SYSTEMPATH = "C:/Users/JanSa/source/repos/tmpGameRepo/";
	//( . ) ( . )
	TextureHolder()
	{
		sf::Texture numbers; 
		numbers.loadFromFile(SYSTEMPATH + "Assets/World/NumsVer3.png");
		m_textures["numbers"] = numbers; 

		sf::Texture tileset_grass;
		tileset_grass.loadFromFile(SYSTEMPATH + "Assets/AssetPack/Pixel Art Top Down - Basic/Texture/TX Tileset Grass.png");
		m_textures["tileset_grass"] = tileset_grass;

		sf::Texture player; 
		player.loadFromFile(SYSTEMPATH + "Assets/Player/Textures/skeletonsprite.png");
		m_textures["skeleton"] = player; 

		sf::Texture cursor; 
		cursor.loadFromFile(SYSTEMPATH + "Assets/AssetPack/Tiny Swords/Tiny Swords (Update 010)/UI/Pointers/01.png");
		m_textures["cursor"] = cursor; 
	}

	const sf::Texture GetTexture(const std::string& ID)
	{
		return this->m_textures[ID];
	}

private:
	std::map<std::string, sf::Texture> m_textures; 
};