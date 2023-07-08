#include "UFO.h"

UFO::UFO()
{
	posx = static_cast <float> (rand () % 640 + 100);
	posy = static_cast <float> (rand() % 480 + 100);
	velx = ((float(rand()) / float(RAND_MAX)) * (0.7f - -0.7f)) + -0.7f;
	vely = ((float(rand()) / float(RAND_MAX)) * (0.7f - -0.7f)) + -0.7f;
	lives = 3;
	numFramesMove = 0;
	alive = true;
	if (!UFOTexture.loadFromFile("UFO.png"))
	{
		std::cout << "error loading file" << std::endl;
		return;
	}
	UFOSprite.setTexture(UFOTexture);
	UFOSprite.setPosition(sf::Vector2f(posx, posy));
	UFOSprite.setOrigin(20.0f, 10.0f);
};

void UFO::changeDirection()
{
	numFramesMove++;
	if (numFramesMove >= rand() % 600 + 120)
	{
		velx = ((float(rand()) / float(RAND_MAX)) * (0.7f - -0.7f)) + -0.7f;
		vely = ((float(rand()) / float(RAND_MAX)) * (0.7f - -0.7f)) + -0.7f;
		numFramesMove = 0;
	}
}

void UFO::move()
{
	UFOSprite.move(velx, vely);
}

int UFO::getLives()
{
	return lives;
}

void UFO::removeLives()
{
	lives--;
}

void UFO::reset()
{
	posx = static_cast <float> (rand() % 640 + 100);
	posy = static_cast <float> (rand() % 480 + 100);
	velx = ((float(rand()) / float(RAND_MAX)) * (0.7f - -0.7f)) + -0.7f;
	vely = ((float(rand()) / float(RAND_MAX)) * (0.7f - -0.7f)) + -0.7f;
	lives = 3;
	numFramesMove = 0;
	alive = true;
}

void UFO::update(bool alive)
{
	if (alive)
	{
		changeDirection();
		move();
	}
}