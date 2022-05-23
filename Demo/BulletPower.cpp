#include "BulletPower.h"

void BulletPower::initSprite(float pos_x, float pos_y)
{
	this->rectSprite.left = 0;
	this->rectSprite.top = 0;
	this->rectSprite.height = 41;
	this->rectSprite.width = 1225 / 25;

	this->clockAnimation.restart();

	this->image.loadFromFile("Textures/power.png");
	this->image.createMaskFromColor(sf::Color(170, 170, 170));
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->rectSprite);
	this->sprite.setPosition(pos_x, pos_y);
}

BulletPower::BulletPower()
{
	this->initSprite(0, 0);
	this->isExist = false;
	this->timeAddNewBulletPower.restart();
	this->clockAnimation.restart();
}

BulletPower::~BulletPower()
{
}

const sf::Vector2f& BulletPower::getPos() const
{
	return this->sprite.getPosition();
}
const sf::FloatRect BulletPower::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
const bool BulletPower::isExistBulletPower() const
{
	return this->isExist;
}

void BulletPower::updateAnimation()
{
	if (this->clockAnimation.getElapsedTime().asSeconds() > 0.05f)
	{
		if (this->rectSprite.left == 1225 - 1225 / 25) {
			this->rectSprite.left = 0;
		}
		else {
			this->rectSprite.left += 1225 / 25;
		}

		this->sprite.setTextureRect(this->rectSprite);
		this->clockAnimation.restart();
	}
}

void BulletPower::updateScale(float scale_x, float scale_y)
{
	this->sprite.scale(scale_x, scale_y);
}

void BulletPower::updatePos(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
}

void BulletPower::updateAddNewBulletPower()
{
	if (this->timeAddNewBulletPower.getElapsedTime().asSeconds() > 10.f) {

		this->isExist = true;
		this->timeAddNewBulletPower.restart();

		float pos_y = 0;
		float pos_x = rand() % 1500 + 50;
		this->initSprite(pos_x, pos_y);
	}
}

void BulletPower::updateMoverment()
{
	this->sprite.move(0.f, 2.f);
}

void BulletPower::update()
{
	if (this->info == false) {
		this->updateAddNewBulletPower();
		this->updateMoverment();
	}

	this->updateAnimation();
}

void BulletPower::render(sf::RenderTarget* target)
{
	if (info == true) {
		target->draw(this->sprite);
		return;
	}

	if(this->isExistBulletPower())
		target->draw(this->sprite);

}


void BulletPower::updateBulletPowerDead()
{
	this->isExist = false;
}


