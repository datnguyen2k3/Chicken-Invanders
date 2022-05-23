#pragma once
#include "Chicken.h"
class ManyChickens
{
private:
	sf::Image imageChicken;
	sf::Texture* texture;
	float distanceWidth;
	float distanceHeight;
	const int CHICKEN_ROWS = 4;
	const int CHICKEN_COLS = 15;
	const int SIZE = CHICKEN_COLS * CHICKEN_ROWS;

	//Move chickens
	float speedMovement;

	//Max speed
	std::vector<float> maxSpeed;
	std::vector<bool> useSpeed;

	//Private functions
	void initTexture();
	void initChickens();
	void initMovement();

public:
	std::vector<Chicken*> chickenList;

	//Constructors and Destructors
	ManyChickens();
	virtual ~ManyChickens();

	const int chickenDead() const;

	//Functions
	void updateChicken();
	void updateMovement();

	//Combat 
	void updateSpeed();
	void update();
	void render(sf::RenderTarget* target);

};

