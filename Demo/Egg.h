#pragma once

#include<SFML/Graphics.hpp>

class Egg
{
private:
	sf::Sprite sprite;

	float speed = 4.f;

	void initVariables(sf::Texture* texture, float pos_x, float pos_y);
public:
	Egg(sf::Texture* texture, float pos_x, float pos_y);
	virtual ~Egg();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const float getWidth() const;
	const float getHeight() const;

	void updateMoveSpeed(float speed);
	void scaleEgg(float scale_x, float scale_y);
	void updateMove();

	void update();
	void render(sf::RenderTarget* target);


};

