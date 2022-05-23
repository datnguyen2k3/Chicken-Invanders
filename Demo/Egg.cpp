#include "Egg.h"

void Egg::initVariables(sf::Texture* texture, float pos_x, float pos_y)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
}

Egg::Egg(sf::Texture* texture, float pos_x, float pos_y)
{
	this->initVariables(texture, pos_x, pos_y);
	this->speed = 4.f;
}

Egg::~Egg()
{

}

const sf::Vector2f& Egg::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Egg::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const float Egg::getWidth() const
{
	return this->sprite.getTexture()->getSize().x;
}

const float Egg::getHeight() const
{
	return this->sprite.getTexture()->getSize().y;
}




void Egg::updateMoveSpeed(float speed)
{
	this->speed = speed;
}

void Egg::scaleEgg(float scale_x, float scale_y)
{
	this->sprite.scale(scale_x, scale_y);
}

void Egg::updateMove()
{
	this->sprite.move(0.f, this->speed);
}

void Egg::update()
{
	this->updateMove();
}

void Egg::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
