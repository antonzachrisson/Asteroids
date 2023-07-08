#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Player
{
	void setDirection();
	void move();
	void tp(int& numFramesTP);
	float posx;
	float posy;
	float velx;
	float vely;
	sf::Texture PlayerTexture;
	std::string direction;
	sf::SoundBuffer teleportBuffer;
	sf::Sound teleport;
	sf::SoundBuffer thrustBuffer;
	sf::Sound thrust;
public:
	Player(float x, float y);
	void update(int& numFramesTP);
	sf::Sprite PlayerSprite;
};
