#include "ManyBullets.h"

void ManyBullets::initTexture(sf::Texture*& texture, std::string path)
{
	texture = new sf::Texture;

	sf::Image image;
	image.loadFromFile(path);
	image.createMaskFromColor(sf::Color(170, 170, 170));
	texture->loadFromImage(image);

}

//Constructors and Destructors
ManyBullets::ManyBullets()
{
	this->levelPower = 0;
	this->textureList.resize(4);
	for (int i = 0; i < textureList.size(); i++) {
		this->initTexture(textureList[i], "Textures/blaster" + std::to_string(i) + ".png");
	}

	this->texture = this->textureList[0];
	this->damage = 1;

	this->soundBullet.openFromFile("Sounds/blaster.wav");
	this->soundLevelUp.openFromFile("Sounds/level_up.wav");
}

ManyBullets::~ManyBullets()
{
	for (auto* bullet : this->bulletList)
	{
		delete bullet;
	}

	delete this->texture;
}

//Functions
void ManyBullets::addBullet(Player*& player)
{
	if (player->isDead())
		return;

	//(sf::Mouse::isButtonPressed(sf::Mouse::Left) || 
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && player->canAttack())
	{
		this->soundBullet.setPlayingOffset(sf::seconds(0.05));
		this->soundBullet.play();

		this->bulletList.push_back(
			new Bullet(this->texture,
			player->getPos().x + 67 / 2.f - this->texture->getSize().x / 2.f,
			player->getPos().y,
			0.f, -1.f, 20.f)
		);

	}
}
//Accessors
const float ManyBullets::getDamage() const
{
	return this->damage;
}

const int ManyBullets::getLevelBullet() const
{
	return this->levelPower + 1;
}

void ManyBullets::updatePowerBullet()
{
	this->soundLevelUp.setPlayingOffset(sf::seconds(0));
	this->soundLevelUp.play();

	if (this->levelPower == this->MAX_LEVEL_POWER)
		return;

	this->levelPower++;
	this->texture = this->textureList[this->levelPower];

	this->damage = float(this->levelPower < this->MAX_LEVEL_POWER ? this->levelPower + 1 : 6);
}

void ManyBullets::resetPowerBullet()
{
	this->levelPower = 0;
	this->texture = this->textureList[0];
	this->damage = 1;
}

void ManyBullets::updateBullet()
{
	for (auto* bullet : this->bulletList)
	{
		bullet->update();
	}
}
void ManyBullets::updateOutOfWindow()
{
	unsigned counter = 0;
	for (auto* bullet : this->bulletList)
	{
		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bulletList.at(counter);
			this->bulletList.erase(this->bulletList.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void ManyBullets::update()
{
	this->updateBullet();
	this->updateOutOfWindow();
}

void ManyBullets::render(sf::RenderTarget* target)
{
	for (auto* bullet : this->bulletList)
	{
		bullet->render(target);
	}
}
