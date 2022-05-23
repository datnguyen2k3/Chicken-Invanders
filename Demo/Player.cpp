#include "Player.h"

//Private functions
void Player::initTexture()
{
	//Player
	this->image.loadFromFile("Textures/spacecraft.png");
	this->image.createMaskFromColor(sf::Color(170, 170, 170));
	this->texture.loadFromImage(this->image);

	//Boom
	this->imageBoom.loadFromFile("Textures/exp.png");
	this->imageBoom.createMaskFromColor(sf::Color(170, 170, 170));
	this->textureBoom.loadFromImage(this->imageBoom);
}

void Player::initVariables()
{
	this->movementSpeed = 10.f;
	this->attackCooldownMax = 200;
	this->attackCooldown = this->attackCooldownMax;

	this->hp = 3;
	this->dead = false;
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Set position
	this->sprite.setPosition(1600.f / 2.f - (float)this->sprite.getTexture()->getSize().x / 2.f - 5.f, 
							 900.f - (float)this->sprite.getTexture()->getSize().y - 5.f);
}

void Player::initGUI()
{
	this->font.loadFromFile("Fonts/font1.ttf");
	this->textDead.setFont(this->font);
	this->textDead.setCharacterSize(75);
	this->textDead.setFillColor(sf::Color::White);
	this->textDead.setString("Press ENTER to revive!");
	this->textDead.setPosition(300, 300);

	this->textWin = this->textDead;
	this->textWin.setString("VICTORY");
	this->textWin.setPosition(400, 300);
	this->textWin.setCharacterSize(150);
	this->textWin.setFillColor(sf::Color::White);


	this->textLose = this->textDead;
	this->textLose.setString("DEFEAT");
	this->textLose.setPosition(480, 300);
	this->textLose.setCharacterSize(150);
	this->textLose.setFillColor(sf::Color::White);
}

//Constructors and Destructors
Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
	this->initGUI();
	this->win = false;
	this->clockAnimationBoom.restart();

	this->soundVictory.openFromFile("Sounds/Victory.wav");
	this->soundDefeat.openFromFile("Sounds/Defeat.wav");
	this->soundDefeat.setVolume(300);
	this->soundBoom.openFromFile("Sounds/exp.wav");
	this->soundBoom.setVolume(50);
	this->soundRevive.openFromFile("Sounds/click.wav");
}

Player::~Player()
{

}

//Accessor
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const bool Player::isDead() const
{
	return this->dead;
}

const float Player::getHp() const
{
	return this->hp;
}

//Functions
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::updateMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->sprite.getPosition().x > 0)
		this->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->sprite.getPosition().y > 0)
		this->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && 
		this->sprite.getPosition().x < 1600 - this->sprite.getTexture()->getSize().x)
		this->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
		this->sprite.getPosition().y < 900 - this->sprite.getTexture()->getSize().y)
		this->move(0.f, 1.f);
}

void Player::outOfWindow(sf::RenderWindow* window)
{
	if (this->getBounds().left < 0.f)
	{
		this->sprite.setPosition(0.f, this->getBounds().top);
	}
	else if (this->getBounds().left + this->getBounds().width >= window->getSize().x)
	{
		this->sprite.setPosition(window->getSize().x - this->getBounds().width, this->getBounds().top);
	}

	if (this->getBounds().top < 0.f)
	{
		this->sprite.setPosition(this->getBounds().left, 0.f);
	}
	else if (this->getBounds().top + this->getBounds().height >= window->getSize().y)
	{
		this->sprite.setPosition( this->getBounds().left, window->getSize().y - this->getBounds().height);
	}

}


//Combat
void Player::setPlayerIsLive()
{
	this->soundRevive.setPlayingOffset(sf::seconds(0));
	this->soundRevive.play();

	this->dead = false;
	this->initSprite();
}
void Player::setPlayerisDead()
{
	this->soundBoom.setPlayingOffset(sf::seconds(0));
	this->soundBoom.play();

	this->dead = true;
	this->hp -= 1.f;
	
	//Boom
	this->clockAnimationBoom.restart();
	this->rectBoom.left = 0;
	this->rectBoom.top = 0;
	this->rectBoom.width = 150;
	this->rectBoom.height = 165;

	this->spriteBoom.setTexture(this->textureBoom);
	this->spriteBoom.setTextureRect(this->rectBoom);
	this->spriteBoom.setPosition(this->sprite.getPosition());

}

void Player::setPlayerWin()
{
	this->soundVictory.play();
	this->win = true;
}

void Player::setPlayerLose()
{
	this->soundDefeat.play();
}

const bool Player::canAttack()
{
	if (this->attackCooldownClock.getElapsedTime().asMilliseconds() >= this->attackCooldownMax)
	{
		this->attackCooldownClock.restart();
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 1.f;
}

void Player::update()
{
	this->updateMove();
	this->updateAttack();
}

void Player::rederBoom(sf::RenderTarget* target)
{
	if (this->clockAnimationBoom.getElapsedTime().asSeconds() > 0.02f && this->rectBoom.left < 1200)
	{
		target->draw(this->spriteBoom);
		this->rectBoom.left += 150;

		this->spriteBoom.setTextureRect(this->rectBoom);
		this->clockAnimationBoom.restart();
	}
	
}

void Player::rederGUI(sf::RenderTarget* target)
{
	target->draw(this->textDead);
}

void Player::render(sf::RenderTarget* target)
{
	if(this->getHp() > 0 && this->isDead() == false)
		target->draw(this->sprite);

	if (this->isDead() == true) {
		this->rederBoom(target);
		if (this->getHp() > 0) this->rederGUI(target);
		else if (this->getHp() <= 0) target->draw(this->textLose);
	}

	if (this->win)
	{
		target->draw(this->textWin);
	}
}
