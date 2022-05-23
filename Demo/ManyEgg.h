#pragma once

#include "Egg.h"
#include <iostream>
#include <vector>

class ManyEgg
{
private:
	sf::Image image;
	sf::Texture* texture;

public:
	std::vector<Egg*> eggList;

	ManyEgg();
	virtual ~ManyEgg();

	void addEgg(float pos_x, float pos_y);

	void outOfWindow();
	void updateRemoveEgg();

	void update();
	void render(sf::RenderTarget* target);


};

