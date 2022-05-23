#include "PointBoard.h"

void PointBoard::initSprite()
{
	this->image.loadFromFile("Textures/pointBoard.png");
	this->image.createMaskFromColor(sf::Color(170, 170, 170));
	this->texture.loadFromImage(image);

	this->sprite.setTexture(texture);
	this->sprite.setPosition(0, 3.f);
}

void PointBoard::initFont()
{
	this->font.loadFromFile("Fonts/font1.ttf");
}

void PointBoard::initText()
{
	this->initText(this->pointsText, 75.f, -1.f);
	this->initText(this->livesText, 220.f, -1.f);
	this->initText(this->levelBulletText, 308.f, -1.f);
	this->initText(this->timePlayText, 30, 50);

}

void PointBoard::initText(sf::Text& text, float pos_x, float pos_y)
{
	text.setFont(this->font);
	text.setCharacterSize(33);
	text.setFillColor(sf::Color::White);
	text.setString("0");
	text.setPosition(pos_x, pos_y);
}

PointBoard::PointBoard()
{
	this->initSprite();
	this->initFont();
	this->initText();
	this->gamePause = false;
	this->gameStart = false;
	this->gameEnd = false;
	this->time = 0;
}

PointBoard::~PointBoard()
{
}

const int PointBoard::getTime() const
{
	return int(time);
}

void PointBoard::start()
{
	if (this->gameStart)
		return;
	this->gameStart = true;
	this->timePlay.restart();
}

void PointBoard::pauseGame()
{
	this->time += float(this->timePlay.getElapsedTime().asSeconds());
	this->gamePause = true;
}

void PointBoard::continueGame()
{
	this->timePlay.restart();
	this->gamePause = false;
}

void PointBoard::endGame()
{
	if (this->gameEnd == true)
		return;

	this->time += this->timePlay.getElapsedTime().asSeconds();
	this->gameEnd = true;
}



void PointBoard::updateScore()
{
	if (this->gamePause == true || this->gameEnd == true) 
		return;

	if (this->timePlay.getElapsedTime().asMilliseconds() < 100.f)
		return;

	this->time += this->timePlay.getElapsedTime().asMilliseconds() / 1000.f;
	this->timePlay.restart();

}

void PointBoard::updateText(int points, int levelBullet, int lives)
{
	this->pointsText.setString(std::to_string(points));
	this->levelBulletText.setString(std::to_string(levelBullet));
	this->livesText.setString(std::to_string(lives));
	this->timePlayText.setString("Time: " + std::to_string(int(this->time)) + "s");
}

void PointBoard::update(int points, int levelBullet, int lives)
{
	this->updateScore();
	this->updateText(points, levelBullet, lives);
}

void PointBoard::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->pointsText);
	target->draw(this->livesText);
	target->draw(this->levelBulletText);
	target->draw(this->timePlayText);
}
