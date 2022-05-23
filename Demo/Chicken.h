#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>

class Chicken
{

private:
	sf::Sprite sprite;

	int type;
	float hp;
	int hpMax;
	int damage;
	int points;

	//Animation
	sf::IntRect rectSprite;
	sf::Clock clockAnimation;

	//Move 
	float speedMovement_x;
	float speedMovement_y;
	float upMax;
	float downMax;
	float leftMax;
	float rightMax;

	//Private functions
	void initSprite(sf::Texture* texture, float pos_x, float pos_y, float movement_speed);
	void initVariables();


public:
	Chicken(sf::Texture* texture, float pos_x, float pos_y, float movement_speed);
	virtual ~Chicken();

	//Get size sprite
	float GetWidth();
	float GetHeight();
	float getSpeed();

	//Accessors
	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPos() const;
	const float getHp() const;

	//Functions
	void getDamage(float damage);

	void updateSpeed(float speed);

	void updateAnimation();
	void updateMovement();

	void update();

	void render(sf::RenderTarget* target);
};

