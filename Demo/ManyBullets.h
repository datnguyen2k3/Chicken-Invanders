#pragma once
#include<iostream>
#include "Bullet.h"
#include "Player.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class ManyBullets
{
private:
	int levelPower;
	const int MAX_LEVEL_POWER = 3;

	sf::Texture* texture;
	std::vector<sf::Texture*> textureList;

	float damage;

	//Sound
	sf::Music soundBullet;
	sf::Music soundLevelUp;

	void initTexture(sf::Texture*& texture, std::string path);

public:
	std::vector<Bullet*> bulletList;

	//Constructors and Destructors
	ManyBullets();
	virtual ~ManyBullets();

	//Functions
	void addBullet(Player*& player);

	//Accessors
	const float getDamage() const;
	const int getLevelBullet() const;

	void updatePowerBullet();
	void resetPowerBullet();

	void updateBullet();
	void updateOutOfWindow();

	void update();
	void render(sf::RenderTarget* target);
};

