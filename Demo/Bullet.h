#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Sprite shape;
	sf::Vector2f direction;
	float movementSpeed;

public:
	//Constructors and Destructors
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

