#include "Game.h"

Game::Game(unsigned int &screenWidth, unsigned int &screenHeight, const char* &title)
{
	screenWidth = 640;
	screenHeight = 480;
	title = "Asteroids";
	bulletsptr = new Bullets(0.0f, 0.0f, 0.0f, true);
	laserBuffer.loadFromFile("laser.wav");
	laser.setBuffer(laserBuffer);
	laser.setVolume(5.0f);
	explosionBuffer.loadFromFile("explosion.wav");
	explosion.setBuffer(explosionBuffer);
	explosion.setVolume(5.0f);

	srand((unsigned int)time(nullptr));
	asteroidsptr = new Asteroids('L', static_cast <float> (rand() % 640 + 100), static_cast <float> (rand() % 480 + 100), ((float(rand()) / float(RAND_MAX)) * (1.0f - -1.0f)) + -1.0f, ((float(rand()) / float(RAND_MAX)) * (1.0f - -1.0f)) + -1.0f);

	numFrames = 0;
	numFramesTP = 0;
	numFramesShoot = 0;
	wave = 0;
	running = true;
	win = false;
};

Game::~Game()
{
	delete bulletsptr;
	delete asteroidsptr;
}

void Game::shoot()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && numFrames > 30)
	{
		sf::Vector2f pos = playerptr.PlayerSprite.getPosition();
		float rot = playerptr.PlayerSprite.getRotation();
		bulletsptr->addPlayerBullet(pos, rot);
		laser.play();
		numFrames = 0;
	}
}

bool Game::Update(float deltaTime)
{
	if (running)
	{
		numFrames += 1;
		numFramesTP += 1;
		GetWave();
		SetWave();
		playerptr.update(numFramesTP);
		asteroidsptr->update();
		shoot();
		ufoShoot(ufoptr.alive);
		worldWrappingGetPos();
		if (bulletsptr != nullptr)
		{
			bulletsptr->update();
		}
		ufoptr.update(ufoptr.alive);
		collision();
		guiptr.update(asteroidsptr);
		checkPlayerLives();
		return true;
	}
	if (win)
	{
		winscreen();
	}
	else
	{
		losescreen();
	}
	return true;
}

void Game::Draw(sf::RenderWindow& window)
{
	window.draw(playerptr.PlayerSprite);
	for (int i = 0; i < asteroidsptr->getNumAsteroids(); i++)
	{
		window.draw(asteroidsptr->getAsteroid(i)->AsteroidSprite);
	}
	if (bulletsptr != nullptr)
	{
		for (int i = 0; i < bulletsptr->getNumBullets('P'); i++)
		{
			window.draw(bulletsptr->getBullet(i, 'P')->shape);
		}
		for (int i = 0; i < bulletsptr->getNumBullets('U'); i++)
		{
			window.draw(bulletsptr->getBullet(i, 'U')->shape);
		}
	}
	window.draw(guiptr.score);
	window.draw(guiptr.lives);
	window.draw(wintxt);
	window.draw(losetxt);
	window.draw(guiptr.wave);
	if(ufoptr.alive) window.draw(ufoptr.UFOSprite);
}

void Game::worldWrappingGetPos()
{
	playerptr.PlayerSprite.setPosition(worldWrappingSetPos(playerptr.PlayerSprite.getPosition()));
	ufoptr.UFOSprite.setPosition(worldWrappingSetPos(ufoptr.UFOSprite.getPosition()));
	for (int i = 0; i < asteroidsptr->getNumAsteroids(); i++)
	{
		asteroidsptr->getAsteroid(i)->AsteroidSprite.setPosition(worldWrappingSetPos(asteroidsptr->getAsteroid(i)->AsteroidSprite.getPosition()));
	}

	for (int i = 0; i < bulletsptr->getNumBullets('P'); i++)
	{
		bulletsptr->getBullet(i, 'P')->shape.setPosition(worldWrappingSetPos(bulletsptr->getBullet(i, 'P')->shape.getPosition()));
	}
}

sf::Vector2f Game::worldWrappingSetPos(sf::Vector2f objectsPos)
{
	if (objectsPos.x < 0.0f)
	{
		objectsPos.x = 640.0f;
	}

	if (objectsPos.x > 640.0f)
	{
		objectsPos.x = 0.0f;
	}

	if (objectsPos.y < 0.0f)
	{
		objectsPos.y = 480.0f;
	}

	if (objectsPos.y > 480.0f)
	{
		objectsPos.y = 0.0f;
	}
	return objectsPos;
}

void Game::collision()
{
	sf::Rect<float> PlayerRect = playerptr.PlayerSprite.getGlobalBounds();
	sf::Rect<float> ufoRect = ufoptr.UFOSprite.getGlobalBounds();
	for (int i = 0; i < asteroidsptr->getNumAsteroids(); i++)
	{
		asteroidsptr->addCollider(i);
	}
	for (int i = 0; i < bulletsptr->getNumBullets('P'); i++)
	{
		bulletsptr->addColliders(i, 'P');
	}
	for (int i = 0; i < bulletsptr->getNumBullets('U'); i++)
	{
		bulletsptr->addColliders(i, 'U');
	}
	if (ufoRect.intersects(PlayerRect) && ufoptr.alive)
	{
		guiptr.removeLives();
		playerptr.PlayerSprite.setPosition(20.0f, 20.0f);
		playerptr.PlayerSprite.setRotation(90.0f);
		explosion.play();
	}
	for (int i = 0; i < bulletsptr->getNumBullets('P'); i++)
	{
		if (bulletsptr->getColliders(i, 'P').intersects(ufoRect) && ufoptr.alive)
		{
			ufoptr.removeLives();
			numFramesShoot = 0;
			bulletsptr->removeBullet('P', i);
			if (ufoptr.getLives() <= 0)
			{
				ufoptr.alive = false;
				explosion.play();
			}
		}
	}
	for (int i = 0; i < asteroidsptr->getNumAsteroids(); i++)
	{
		if (asteroidsptr->getCollider(i).intersects(PlayerRect))
		{
			guiptr.removeLives();
			playerptr.PlayerSprite.setPosition(20.0f, 20.0f);
			playerptr.PlayerSprite.setRotation(90.0f);
			explosion.play();
		}
	}
	for (int i = 0; i < bulletsptr->getNumBullets('P'); i++)
	{
		for (int j = 0; j < asteroidsptr->getNumAsteroids(); j++)
		{
			if (asteroidsptr->getCollider(j).intersects(bulletsptr->getColliders(i, 'P')))
			{
				asteroidsptr->getAsteroid(j)->removeLives();
				if (asteroidsptr->getAsteroid(j)->getLives() <= 0)
				{
					explosion.play();
				}
				bulletsptr->removeBullet('P', i);
			}
		}
	}
	for (int i = 0; i < bulletsptr->getNumBullets('U'); i++)
	{
		if (bulletsptr->getColliders(i, 'U').intersects(PlayerRect) && ufoptr.alive)
		{
			guiptr.removeLives();
			playerptr.PlayerSprite.setPosition(20.0f, 20.0f);
			playerptr.PlayerSprite.setRotation(90.0f);
			explosion.play();
			bulletsptr->removeBullet('U', i);
		}
	}
	asteroidsptr->clearColliders();
	bulletsptr->clearColliders('P');
	bulletsptr->clearColliders('U');
}

void Game::GetWave()
{
	if (asteroidsptr->asteroidsSize() == 0 && wave == 5)
	{
		win = true;
		running = false;
	}
	else if (asteroidsptr->asteroidsSize() == 0)
	{
		wave++;
		guiptr.setWave(wave);
		ufoptr.reset();
	}
}

void Game::SetWave()
{
	if (asteroidsptr->asteroidsSize() == 0)
	{
		playerptr.PlayerSprite.setPosition(20.0f, 20.0f);
		playerptr.PlayerSprite.setRotation(90.0f);
		srand((unsigned int)time(nullptr));
		for (int i = 0; i < wave; i++)
		{
			asteroidsptr->addAsteroids();
			asteroidsptr->addNumAsteroids();
		}
	}
}

void Game::checkPlayerLives()
{
	if (guiptr.getLives() <= 0)
	{
		win = false;
		running = false;
	}
}

void Game::winscreen()
{
	wintxt.setFont(guiptr.font);
	wintxt.setString("YOU WIN!");
	wintxt.setCharacterSize(30);
	wintxt.setFillColor(sf::Color::White);
	sf::Rect<float> rect = wintxt.getLocalBounds();
	wintxt.setPosition((640.0f - rect.width) / 2, (480.0f - rect.height) / 2);
}

void Game::losescreen()
{
	losetxt.setFont(guiptr.font);
	losetxt.setString("YOU LOSE!");
	losetxt.setCharacterSize(30);
	losetxt.setFillColor(sf::Color::White);
	sf::Rect<float> rect = losetxt.getLocalBounds();
	losetxt.setPosition((640.0f - rect.width) / 2, (480.0f - rect.height) / 2);
}

void Game::ufoShoot(bool alive)
{
	if(alive) numFramesShoot++;
	if (numFramesShoot >= rand() % 1200 + 240 && alive)
	{
		sf::Vector2f ufopos = ufoptr.UFOSprite.getPosition();
		sf::Vector2f playerpos = playerptr.PlayerSprite.getPosition();
		float x = ufopos.x - playerpos.x;
		float y = ufopos.y - playerpos.y;
		float hyp = sqrt((x * x) + (y * y));
		float rot;
		if (y >= 0)
		{
			rot = (acosf(x / hyp) * (180.0f / (atanf(1) * 4))) - 90.0f;
		}
		else
		{
			rot = -(acosf(x / hyp) * (180.0f / (atanf(1) * 4))) - 90.0f;
		}
		bulletsptr->addUfoBullet(ufopos, rot);
		laser.play();
		numFramesShoot = 0;
	}
}
