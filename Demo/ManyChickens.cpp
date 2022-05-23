#include "ManyChickens.h"
//Private functions
void ManyChickens::initTexture()
{
	this->imageChicken.loadFromFile("Textures/chicken_red.png");
	this->imageChicken.createMaskFromColor(sf::Color(170, 170, 170));
	this->texture = new sf::Texture;
	this->texture->loadFromImage(this->imageChicken);
}

void ManyChickens::initChickens()
{
	this->distanceHeight = 40.0f;
	this->distanceWidth = 25.0f;

	this->maxSpeed.resize(4);
	for (int i = 0; i < this->maxSpeed.size(); i++) {
		this->maxSpeed[i] = 3.f + 1.5f * i;
	}

	for (int i = 0; i < this->CHICKEN_COLS; i++) {
		for (int j = 0; j < this->CHICKEN_ROWS; j++) {
			this->chickenList.push_back(new Chicken(this->texture, i * (75 + distanceWidth), j * (68 + distanceWidth), 1.0f));
		}
	}
}

void ManyChickens::initMovement()
{
	this->speedMovement = 5.0f;
}

//Constructors and Destructors
ManyChickens::ManyChickens()
{
	this->initTexture();
	this->initChickens();
	this->initMovement();

	this->useSpeed.resize(4);
}

ManyChickens::~ManyChickens()
{
	for (auto* chicken : this->chickenList)
	{
		delete chicken;
	}

	delete this->texture;
}

const int ManyChickens::chickenDead() const
{
	return this->SIZE - this->chickenList.size();
}

//Functions
void ManyChickens::updateChicken()
{
	for (auto* chicken : this->chickenList)
	{
		chicken->update();
	}
}

void ManyChickens::updateMovement()
{

}

void ManyChickens::updateSpeed()
{
	if (this->chickenList.size() == 0)
		return;

	//int levelSpeed = std::min(this->SIZE / this->chickenList.size(), this->maxSpeed.size()) - 1;

	if (this->chickenList.size() < 30 && this->useSpeed[0] == false) {
		this->useSpeed[0] = true;
		for (auto* chicken : this->chickenList)
			chicken->updateSpeed(this->maxSpeed[0]);
	}
	//if (this->chickenList.size() < 20 && this->useSpeed[1] == false) {
	//	this->useSpeed[1] = true;
	//	for (auto* chicken : this->chickenList)
	//		chicken->updateSpeed(this->maxSpeed[1]);
	//}
	//if (this->chickenList.size() < 10 && this->useSpeed[2] == false) {
	//	this->useSpeed[2] = true;
	//	for (auto* chicken : this->chickenList)
	//		chicken->updateSpeed(this->maxSpeed[2]);
	//}


}

void ManyChickens::update()
{
	this->updateChicken();
	this->updateSpeed();
}

void ManyChickens::render(sf::RenderTarget* target)
{
	for (auto* chicken : this->chickenList)
	{
		chicken->render(target);
	}
}
