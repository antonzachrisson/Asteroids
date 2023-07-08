#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <time.h>
#include <cmath>

class Asteroids
{
	void move();
	void multiply();
	float posx;
	float posy;
	float velx;
	float vely;
	char scale;
	int lives;
	int numAsteroids;
	Asteroids* temp;
	sf::Texture AsteroidTexture;
	std::vector<Asteroids*> asteroids;
	std::vector<sf::Rect<float>> Colliders;
public:
	Asteroids(char scale_, float posx_, float posy_, float velx_, float vely_);
	~Asteroids();
	void update();
	int getNumAsteroids();
	int getLives();
	void addNumAsteroids();
	void removeLives();
	void addAsteroids();
	void addCollider(int index);
	sf::Rect<float> getCollider(int index);
	void clearColliders();
	int asteroidsSize();
	Asteroids* getAsteroid(int index);
	sf::Sprite AsteroidSprite;
};
