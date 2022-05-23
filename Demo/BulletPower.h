#pragma once

#include<SFML/Graphics.hpp>

class BulletPower
{
private:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	bool isExist;
	sf::Clock timeAddNewBulletPower;


	//Animation
	sf::IntRect rectSprite;
	sf::Clock clockAnimation;

	void initSprite(float pos_x, float pos_y);

public:
	BulletPower();
	virtual ~BulletPower();

	bool info = false;

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const bool isExistBulletPower() const;
	
	void updateScale(float scale_x, float scale_y);
	void updatePos(float pos_x, float pos_y);

	void updateAddNewBulletPower();
	void updateAnimation();
	void updateMoverment();
	void update();

	void updateBulletPowerDead();

	void render(sf::RenderTarget* target);


};

