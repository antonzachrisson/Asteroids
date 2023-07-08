#include "Asteroid.h"

Asteroids::Asteroids(char scale_, float posx_, float posy_, float velx_, float vely_)
{
	posx = posx_;
	posy = posy_;
	velx = velx_;
	vely = vely_;
	lives = 2;
	numAsteroids = 0;
	scale = scale_;
	temp = nullptr;
	
	if (!AsteroidTexture.loadFromFile("Asteroid.png"))
	{
		std::cout << "error loading file" << std::endl;
		return;
	}
	AsteroidSprite.setTexture(AsteroidTexture);
	AsteroidSprite.setPosition(sf::Vector2f(posx, posy));
	if (scale == 'L')
	{
		AsteroidSprite.setOrigin(51.0f / 2.0f, 46.0f / 2.0f);
	}
	if (scale == 'M')
	{
		AsteroidSprite.scale(0.5f, 0.5f);
		AsteroidSprite.setOrigin(51.0f / 4.0f, 46.0f / 4.0f);
	}
	if (scale == 'S')
	{
		AsteroidSprite.scale(0.25f, 0.25f);
		AsteroidSprite.setOrigin(51.0f / 8.0f, 46.0f / 8.0f);
	}
};

Asteroids::~Asteroids()
{
	for (int i = 0; i < numAsteroids; i++)
	{
		delete asteroids[i];
	}
};

void Asteroids::move()
{
	for (int i = 0; i < numAsteroids; i++)
	{
		asteroids[i]->AsteroidSprite.move(asteroids[i]->velx, asteroids[i]->vely);
		asteroids[i]->posx += asteroids[i]->velx;
		asteroids[i]->posy += asteroids[i]->vely;
	}
}

void Asteroids::multiply()
{
	for (int i = 0; i < numAsteroids; i++)
	{
		if (asteroids[i]->lives <= 0)
		{
			std::vector<Asteroids*>::size_type index = numAsteroids;
			sf::Vector2f position = asteroids[i]->AsteroidSprite.getPosition();
			char scale = asteroids[i]->scale;
			temp = asteroids[i];
			asteroids[i] = asteroids[index - 1];
			asteroids[index - 1] = temp;
			asteroids.pop_back();
			numAsteroids--;
			float vectorLength = sqrt((temp->velx * temp->velx) + (temp->vely * temp->vely));
			float angle1 = acos(temp->velx / vectorLength) + 0.52f;
			float angle2 = acos(temp->velx / vectorLength) - 0.52f;
			float velx1 = cos(angle1) * vectorLength;
			float vely1 = sin(angle1) * vectorLength;
			float velx2 = cos(angle2) * vectorLength;
			float vely2 = sin(angle2) * vectorLength;

			if (scale == 'L')
			{
				asteroids.push_back(new Asteroids('M', position.x, position.y, velx1, vely1));
				asteroids.push_back(new Asteroids('M', position.x, position.y, velx2, vely2));
				numAsteroids += 2;
			}
			else if (scale == 'M')
			{
				asteroids.push_back(new Asteroids('S', position.x, position.y, velx1, vely1));
				asteroids.push_back(new Asteroids('S', position.x, position.y, velx2, vely2));
				numAsteroids += 2;
			}
		}
	}
}

int Asteroids::getNumAsteroids()
{
	return numAsteroids;
}

int Asteroids::getLives()
{
	return lives;
}

void Asteroids::addNumAsteroids()
{
	numAsteroids++;
}

void Asteroids::removeLives()
{
	lives--;
}

void Asteroids::addAsteroids()
{
	asteroids.push_back(new Asteroids('L', static_cast <float> (rand() % 640 + 100), static_cast <float> (rand() % 480 + 100), ((float(rand()) / float(RAND_MAX)) * (1.0f - -1.0f)) + -1.0f, ((float(rand()) / float(RAND_MAX)) * (1.0f - -1.0f)) + -1.0f));
}

void Asteroids::addCollider(int index)
{
	Colliders.push_back(asteroids[index]->AsteroidSprite.getGlobalBounds());
}

int Asteroids::asteroidsSize()
{
	return int(asteroids.size());
}

Asteroids* Asteroids::getAsteroid(int index)
{
	return asteroids[index];
}

sf::Rect<float> Asteroids::getCollider(int index)
{
	return Colliders[index];
}

void Asteroids::clearColliders()
{
	Colliders.clear();
}

void Asteroids::update()
{
	multiply();
	move();
}
