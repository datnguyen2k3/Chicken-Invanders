#include "ManyEggBoss.h"

ManyEggBoss::ManyEggBoss()
{
	this->image.loadFromFile("Textures/egg_boss.png");
	this->image.createMaskFromColor(sf::Color(170, 170, 170));
	this->texture = new sf::Texture;
	this->texture->loadFromImage(this->image);
}

ManyEggBoss::~ManyEggBoss()
{
	delete this->texture;
	for (auto* egg : this->eggList)
	{
		delete egg;
	}
}

const sf::Vector2u ManyEggBoss::getSize() const
{
	return this->texture->getSize();
}

void ManyEggBoss::addEgg(float pos_x, float pos_y)
{
	Egg* egg = new Egg(this->texture, pos_x, pos_y);
	egg->updateMoveSpeed(15.f);
	this->eggList.push_back(egg);
}

void ManyEggBoss::outOfWindow()
{
	for (auto* egg : this->eggList)
	{
		if (egg->getPos().y > 900 + egg->getHeight())
			delete egg;
	}
}

void ManyEggBoss::updateRemoveEggBoss()
{
	this->outOfWindow();

}

void ManyEggBoss::update()
{
	for (auto* egg : this->eggList)
	{
		egg->update();
	}
}

void ManyEggBoss::render(sf::RenderTarget* target)
{
	for (auto* egg : this->eggList)
	{
		egg->render(target);
	}
}
