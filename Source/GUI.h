#pragma once

#include "SFML/Graphics.hpp"
#include "Asteroid.h"
#include <string>
#include <iostream>

class GUI
{
	void getScore(Asteroids* asteroidsptr);
	void setScore();
	void setLives();
	int Score;
	int Lives;
	std::string strLives;
	std::string strWave;
public:
	GUI();
	void setWave(int wave_);
	void update(Asteroids* asteroidsptr);
	int getLives();
	void removeLives();
	sf::Font font;
	sf::Text score;
	sf::Text lives;
	sf::Text wave;
};
