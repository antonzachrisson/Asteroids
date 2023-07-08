#include "Player.h"
#include <iostream>
#include <time.h>

Player::Player(float x, float y)
{
	posx = x;
	posy = y;
	velx = 1.0f;
	vely = 0.0f;
	if (!PlayerTexture.loadFromFile("Player.png"))
	{
		std::cout << "error loading file" << std::endl;
		return;
	}
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setPosition(sf::Vector2f(x, y));
	PlayerSprite.setOrigin(9.5f, 10.0f);
	PlayerSprite.setRotation(90.0f);
	teleportBuffer.loadFromFile("teleport.wav");
	teleport.setBuffer(teleportBuffer);
	teleport.setVolume(5.0f);
	thrustBuffer.loadFromFile("thrust.wav");
	thrust.setBuffer(thrustBuffer);
	thrust.setVolume(5.0f);
	srand(static_cast<unsigned int>(time(nullptr)));
};

void Player::setDirection()
{
	direction = "null";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = "up";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		PlayerSprite.setRotation(PlayerSprite.getRotation() - 2.5f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		PlayerSprite.setRotation(PlayerSprite.getRotation() + 2.5f);
	}
}

void Player::move()
{
	if (velx > 2.0f)
	{
		velx = 2.0f;
	}

	if (velx < -2.0f)
	{
		velx = -2.0f;
	}

	if (vely > 2.0f)
	{
		vely = 2.0f;
	}

	if (vely < -2.0f)
	{
		vely = -2.0f;
	}

	if (direction == "null")
	{
		if (velx > -0.04f && velx < 0.04f && vely > -0.04f && vely < 0.04f)
		{
			velx = 0.0f;
			vely = 0.0f;
		}
		if (velx > 0.0f)
		{
			velx -= 0.04f;
		}
		if (velx < 0.0f)
		{
			velx += 0.04f;
		}
		if (vely > 0.0f)
		{
			vely -= 0.04f;
		}
		if (vely < 0.0f)
		{
			vely += 0.04f;
		}
		thrust.stop();
	}
	
	else
	{
		float rot = PlayerSprite.getRotation();
		vely -= cosf(rot / (180.0f / (atan(1.0f) * 4.0f))) / 15.0f;
		velx += sinf(rot / (180.0f / (atan(1.0f) * 4.0f))) / 15.0f;
		if (thrust.getStatus() == sf::Sound::Status::Stopped)
		{
			thrust.play();
		}
	}
	
	PlayerSprite.move(velx, vely);
}

void Player::tp(int &numFramesTP)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && numFramesTP > 400)
	{
		float x = static_cast<float>(rand() % 640);
		float y = static_cast<float>(rand() % 480);
		PlayerSprite.setPosition(x, y);
		teleport.play();
		numFramesTP = 0;
	}
}

void Player::update(int& numFramesTP)
{
	setDirection();
	move();
	tp(numFramesTP);
}