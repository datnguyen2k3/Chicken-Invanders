#pragma once
#include<SFML/Graphics.hpp>

class EggBig
{
private:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	bool isExist;
	sf::Clock timeAddNewEggBig;

	void initSprite();
public:
	EggBig();
	virtual ~EggBig();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	void updateMovement();

	void update();
	void render(sf::RenderTarget* target);

};

