#pragma once

#include "SFML/Graphics.hpp"
#include<iostream>

class UFO
{
	float posx;
	float posy;
	float velx;
	float vely;
	int lives;
	int numFramesMove;
	sf::Texture UFOTexture;
	void move();
	void changeDirection();
public:
	UFO();
	void update(bool alive);
	int getLives();
	void removeLives();
	void reset();
	sf::Sprite UFOSprite;
	bool alive;
};

