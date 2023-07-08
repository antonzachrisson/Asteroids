#pragma once

#include "SFML/Graphics.hpp"
#include <list>
#include <cmath>

class Bullets
{
	float posx;
	float posy;
	float velx;
	float vely;
	Bullets* temp;
	std::vector<Bullets*> bullets;
	std::vector<Bullets*> ufobullets;
	int numbullets = 0;
	int ufonumbullets = 0;
	int numFrames;
	int lifetime;
	std::vector<sf::Rect<float>> Colliders;
	std::vector<sf::Rect<float>> ufoColliders;
	void move();
public:
	Bullets(float x, float y, float rot, bool player);
	~Bullets();
	void update();
	void removeBullet(char type, int index);
	void addUfoBullet(sf::Vector2f pos, float rot);
	void addPlayerBullet(sf::Vector2f pos, float rot);
	sf::Rect<float> getColliders(int index, char type);
	void addColliders(int index, char type);
	void clearColliders(char type);
	int getNumBullets(char type);
	Bullets* getBullet(int index, char type);
	sf::RectangleShape shape{ sf::Vector2f(3.0f, 10.0f) };
};
