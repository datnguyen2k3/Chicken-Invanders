#include "Chicken.h"

void Chicken::initSprite(sf::Texture* texture, float pos_x, float pos_y, float movement_speed)
{
	this->rectSprite.left = 0;
	this->rectSprite.top = 0;
	this->rectSprite.height = 68;
	this->rectSprite.width = 75;

	this->sprite.setTexture(*texture);
	this->sprite.setTextureRect(this->rectSprite);
	this->sprite.setPosition(pos_x, pos_y);

	this->clockAnimation.restart();
}

void Chicken::initVariables()
{
	this->type    = 0;
	this->hp      = 6;
	this->hpMax   = 6;
	this->damage  = 1;
	this->points  = 5;

	//Movement -> need change
	this->speedMovement_x = 1.5f;
	this->speedMovement_y = 1.5f;
	this->upMax = -200;
	this->downMax = 1100;
	this->leftMax = 1800;
	this->rightMax = -200;
}

Chicken::Chicken(sf::Texture* texture, float pos_x, float pos_y, float movement_speed)
{
	this->initSprite(texture, pos_x, pos_y, movement_speed);
	this->initVariables(); 
	this->clockAnimation.restart();

}

Chicken::~Chicken()
{

}


//Get size sprite
float Chicken::GetWidth()
{
	return 68;
}
float Chicken::GetHeight()
{
	return 75;
}

float Chicken::getSpeed()
{
	return this->speedMovement_x;
}

//Accessors
const sf::FloatRect Chicken::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
const sf::Vector2f& Chicken::getPos() const
{
	return this->sprite.getPosition();
}
const float Chicken::getHp() const
{
	return this->hp;
}

void Chicken::getDamage(float damage)
{
	this->hp -= damage;
}

void Chicken::updateSpeed(float speed)
{
	this->speedMovement_x /= this->speedMovement_x;
	this->speedMovement_x *= speed;
	this->speedMovement_y /= this->speedMovement_y;
	this->speedMovement_y *= speed;
}

void Chicken::updateAnimation()
{
	if (this->clockAnimation.getElapsedTime().asSeconds() > 0.05f)
	{
		if (this->rectSprite.left == 1350 - 75) {
			this->rectSprite.left = 0;
		}
		else {
			this->rectSprite.left += 75;
		}

		this->sprite.setTextureRect(this->rectSprite);
		this->clockAnimation.restart();
	}
}

void Chicken::updateMovement()
{

	if (this->sprite.getPosition().y <= this->upMax)
	{
		this->speedMovement_y *= -1.0f;
	}
	if (this->sprite.getPosition().y >= this->downMax)
	{
		this->speedMovement_y *= -1.0f;
	}
	if (this->sprite.getPosition().x <= this->leftMax)
	{
		this->speedMovement_x *= -1.0f;
	}
	if (this->sprite.getPosition().x >= this->rightMax)
	{
		this->speedMovement_x *= -1.0f;
	}
	this->sprite.move(this->speedMovement_x, this->speedMovement_y);
}


void Chicken::update()
{
	this->updateAnimation();
	this->updateMovement();
}

void Chicken::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}


