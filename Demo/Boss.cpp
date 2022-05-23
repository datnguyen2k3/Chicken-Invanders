#include "Boss.h"
//#include <cmath>

void Boss::initSprite()
{
	this->rectSprite.left = 0;
	this->rectSprite.top = 0;
	this->rectSprite.height = 117;
	this->rectSprite.width = 200;


	this->image.loadFromFile("Textures/boss.png");
	this->image.createMaskFromColor(sf::Color(170, 170, 170));
	this->texture.loadFromImage(this->image);
	
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->rectSprite);
	this->sprite.scale(1.5f, 1.5f);
	this->sprite.setPosition(-116, -199);

}

void Boss::initMovement()
{
	this->speedMovement_x = 3.f;
	this->speedMovement_y = 3.f;
	this->upMax = -200;
	this->downMax = 900;
	this->leftMax = -117;
	this->rightMax = 1600;
}

void Boss::initBoom()
{
	this->imageBoom.loadFromFile("Textures/exp.png");
	this->imageBoom.createMaskFromColor(sf::Color(170, 170, 170));
	this->textureBoom.loadFromImage(this->imageBoom);

}

Boss::Boss()
{
	this->initSprite();
	this->initMovement();
	this->initBoom();
	this->dead = false;
	this->hp = this->HP_MAX;

	this->usedSpeed = false;

	this->boom.openFromFile("Sounds/exp.wav");
}

Boss::~Boss()
{
}

const sf::Vector2u Boss::getSize() const
{
	return this->texture.getSize();
}
const sf::FloatRect Boss::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
const sf::Vector2f& Boss::getPos() const
{
	return this->sprite.getPosition();
}
const float Boss::getHp() const
{
	return this->hp;
}
const bool Boss::isDead() const
{
	return this->dead;
}
void Boss::getDamge(float damage)
{
	this->hp -= damage;
}

void Boss::setBossDead()
{
	this->boom.play();

	this->dead = true;

	this->clockAnimationBoom.restart();
	this->rectBoom.left = 0;
	this->rectBoom.top = 0;
	this->rectBoom.width = 150;
	this->rectBoom.height = 165;

	this->spriteBoom.setTexture(this->textureBoom);
	this->spriteBoom.setTextureRect(this->rectBoom);
	this->spriteBoom.setPosition(this->sprite.getPosition());

}


void Boss::updateSpeed()
{
	if (this->usedSpeed == true)
		return;

	if (this->hp < this->HP_MAX / 2)
	{
		this->usedSpeed = true;
		this->speedMovement_x /= abs(this->speedMovement_x);
		this->speedMovement_x *= 6;
		this->speedMovement_y /= abs(this->speedMovement_y);
		this->speedMovement_y *= 6;
	}
}

void Boss::updateMovement()
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

void Boss::updateAnimation()
{
	if (this->clockAnimation.getElapsedTime().asSeconds() > 0.05f)
	{
		if (this->rectSprite.left == 2000 - 200) {
			this->rectSprite.left = 0;
		}
		else {
			this->rectSprite.left += 200;
		}

		this->sprite.setTextureRect(this->rectSprite);
		this->clockAnimation.restart();
	}
}

void Boss::update()
{
	if (this->isDead() == false) {
		this->updateMovement();
		this->updateAnimation();
		this->updateSpeed();
	}
}

void Boss::rederBoom(sf::RenderTarget* target)
{
	if (this->clockAnimationBoom.getElapsedTime().asSeconds() > 0.02f && this->rectBoom.left < 1200)
	{
		this->spriteBoom.scale(3, 3);
		target->draw(this->spriteBoom);
		this->spriteBoom.scale(1.f / 3, 1.f / 3);

		this->rectBoom.left += 150;
		this->spriteBoom.setTextureRect(this->rectBoom);
		this->clockAnimationBoom.restart();
	}
}

void Boss::render(sf::RenderTarget* target)
{
	if(this->isDead() == false)
		target->draw(this->sprite);
	else 
	{
		this->rederBoom(target);
	}
}
