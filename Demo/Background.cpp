#include "Background.h"

void Background::initVariables()
{
	this->texture.loadFromFile("Textures/background.png");

	this->rectSourceSprite.left = 0;
	this->rectSourceSprite.top = 0;
	this->rectSourceSprite.width = 1600;
	this->rectSourceSprite.height = 900;

	this->sprite.setTexture(texture);
	this->sprite.scale(16 / 12.f, 1.0f);
	this->sprite.setTextureRect(rectSourceSprite);

}

Background::Background()
{
	this->initVariables();
}

Background::~Background()
{

}

void Background::update()
{
	if (clock.getElapsedTime().asSeconds() > 0.1f)
	{
		if (rectSourceSprite.top >= 3840 - 900) {
			rectSourceSprite.top = 0;
		}
		else {
			rectSourceSprite.top += 2;
		}

		sprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
}

void Background::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
