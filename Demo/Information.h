#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "BulletPower.h"

class Information
{
private:
	//Background
	sf::Texture textureBackground;
	sf::Sprite spriteBackground;

	//Image bullet

	//Text
	sf::Font font;
	sf::Font font2;
	sf::Text Atext, Wtext, Dtext, Stext;
	sf::Text moveText;
	sf::Text fireText;
	sf::Text introText;

	sf::Text clickText;

	sf::Text levelBulletText;

	sf::Text authorText;

	//Insert image power
	BulletPower bulletPower;

	//Back button
	sf::Text backText;

	//Sound
	sf::Music singleClick;
	sf::Music click;

	void initText();
	void initText(sf::Text& text, std::string word, sf::Vector2f pos);

	//Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	Information();
	virtual ~Information();

	bool open;
	const bool isOpen() const;
	const sf::FloatRect getBackBounds() const;

	void run(sf::RenderWindow* window);

	void updateMouse(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);

};

