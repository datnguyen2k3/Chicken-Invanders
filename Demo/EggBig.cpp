#include "EggBig.h"

void EggBig::initSprite()
{
}

EggBig::EggBig()
{
	this->image.loadFromFile("Textures/egg_boss.png");
	this->image.createMaskFromColor(sf::Color(170, 170, 170));
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
}

EggBig::~EggBig()
{
}

const sf::Vector2f& EggBig::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect EggBig::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void EggBig::updateMovement()
{
	this->sprite.move(0, 10.f);
}

void EggBig::update()
{
	this->updateMovement();
}

void EggBig::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
