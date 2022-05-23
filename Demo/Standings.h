#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<algorithm>
#include<fstream>

class Standings
{
private:
	sf::Texture textureBackground;
	sf::Sprite spriteBackground;

	sf::Font font;

	const int SIZE_STANDINGS = 5;
	std::string standingStr;
	sf::Text standingText;

	//Back button
	sf::Text backText;

	//Sound
	sf::Music singleClick;
	sf::Music click;

	int gameEnd;

	void initText(sf::Text& text, std::string word, sf::Vector2f pos);

	//Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	Standings();
	virtual ~Standings();

	void push(int score);

	bool open = false;
	void run(sf::RenderWindow* window);

	const sf::FloatRect getBackBounds() const;

	void updateMouse(sf::RenderWindow* window);
	void updateStandingStr();
	void updateClick();
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);

};

