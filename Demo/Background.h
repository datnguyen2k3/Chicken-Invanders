#pragma once

#include<SFML/Graphics.hpp>

class Background
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rectSourceSprite;
	sf::Clock clock;

	void initVariables();
public:
	Background();
	virtual ~Background();

	void update();
	void render(sf::RenderTarget* target);
};

