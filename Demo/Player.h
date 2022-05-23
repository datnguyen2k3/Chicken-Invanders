#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>

class Player
{
private:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;

	sf::Clock attackCooldownClock;

	//Combat
	float hp;
	bool dead;
	bool win = false;

	//BOOM
	sf::Image imageBoom;
	sf::Texture textureBoom;
	sf::Sprite spriteBoom;
	sf::Clock clockAnimationBoom;
	sf::IntRect rectBoom;

	//GUI when player is dead
	sf::Font font;
	sf::Text textDead;

	sf::Text textWin;
	sf::Text textLose;

	sf::Music soundVictory;
	sf::Music soundDefeat;
	sf::Music soundBoom;
	sf::Music soundRevive;

	//Private functions
	void initVariables();
	void initSprite();
	void initTexture();
	void initGUI();


public:
	//Constructors and Destructors
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const bool isDead() const;
	const float getHp() const;

	//Functions
	void move(const float dirX, const float dirY);
	void updateMove();
	void outOfWindow(sf::RenderWindow* window);

	//Combat
	void setPlayerIsLive();
	void setPlayerisDead();
	void setPlayerWin();
	void setPlayerLose();

	const bool canAttack();
	void updateAttack();

	void update();

	void rederBoom(sf::RenderTarget* target);
	void rederGUI(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

