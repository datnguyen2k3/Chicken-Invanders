#include "ManyEgg.h"

ManyEgg::ManyEgg()
{
	this->image.loadFromFile("Textures/egg.png");
	this->image.createMaskFromColor(sf::Color(170, 170, 170));
	this->texture = new sf::Texture;
	this->texture->loadFromImage(this->image);
}

ManyEgg::~ManyEgg()
{
	delete this->texture;
	for (auto* egg : this->eggList)
	{
		delete egg;
	}
}

void ManyEgg::addEgg(float pos_x, float pos_y)
{
	this->eggList.push_back(new Egg(this->texture, pos_x, pos_y));
}

void ManyEgg::outOfWindow()
{
	for (auto* egg : this->eggList) 
	{
		if (egg->getPos().y > 900 + egg->getHeight())
			delete egg;
	}
}

void ManyEgg::updateRemoveEgg()
{
	this->outOfWindow();
}



void ManyEgg::update()
{
	for (auto* egg : this->eggList) 
	{
		egg->update();
	}
}

void ManyEgg::render(sf::RenderTarget* target)
{
	for (auto* egg : this->eggList)
	{
		egg->render(target);
	}
}
