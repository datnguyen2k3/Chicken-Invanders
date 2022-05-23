#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class Boss
{
private:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	const float HP_MAX = 400.f;
	float hp =  HP_MAX;

	//Animation
	sf::IntRect rectSprite;
	sf::Clock clockAnimation;

	//BOOM
	sf::Image imageBoom;
	sf::Texture textureBoom;
	sf::Sprite spriteBoom;
	sf::Clock clockAnimationBoom;
	sf::IntRect rectBoom;

	bool dead = false;

	//Moverment
	float speedMovement_x;
	float speedMovement_y;
	float upMax;
	float downMax;
	float leftMax;
	float rightMax;

	sf::Music boom;

	bool usedSpeed;

	void initSprite();
	void initMovement();
	void initBoom();
public:
	Boss();
	virtual ~Boss();

	const sf::Vector2u getSize() const;
	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPos() const;
	const float getHp() const;
	const bool isDead() const;

	void getDamge(float damage);

	void setBossDead();

	void updateSpeed();
	void updateMovement();
	void updateAnimation();
	void update();

	void rederBoom(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);




};

