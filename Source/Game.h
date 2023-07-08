#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Asteroid.h"
#include "Bullets.h"
#include "GUI.h"
#include "Player.h"
#include "UFO.h"
#include <iostream>

class Game
{
	void shoot();
	void ufoShoot(bool alive);
	void worldWrappingGetPos();
	void collision();
	void SetWave();
	void GetWave();
	void checkPlayerLives();
	void winscreen();
	void losescreen();
	sf::Vector2f worldWrappingSetPos(sf::Vector2f objectsPos);
	sf::Text wintxt;
	sf::Text losetxt;
	sf::SoundBuffer laserBuffer;
	sf::Sound laser;
	sf::SoundBuffer explosionBuffer;
	sf::Sound explosion;
	Player playerptr = Player(20.0f, 20.0f);
	Bullets* bulletsptr = nullptr;
	Asteroids* asteroidsptr = nullptr;
	GUI guiptr;
	UFO ufoptr;
	int numFrames;
	int numFramesTP;
	int numFramesShoot;
	int wave;
	bool running;
	bool win;
public:
	Game(unsigned int& screenWidth, unsigned int& screenHeight, const char*& title);
	~Game();
	bool Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};