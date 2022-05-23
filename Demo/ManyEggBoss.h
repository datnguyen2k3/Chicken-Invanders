#pragma once

#include "Egg.h"
#include <iostream>
#include <vector>

class ManyEggBoss
{
private:
	sf::Image image;
	sf::Texture* texture;

public:
	std::vector<Egg*> eggList;

	ManyEggBoss();
	virtual ~ManyEggBoss();

	const sf::Vector2u getSize() const;

	void addEgg(float pos_x, float pos_y);

	void outOfWindow();
	void updateRemoveEggBoss();


	void update();
	void render(sf::RenderTarget* target);


};

