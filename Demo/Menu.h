#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

class Menu
{
private:
	sf::Texture textureBackground;
	sf::Sprite spriteBackground;

	sf::Texture textureLogo;
	sf::Sprite spriteLogo;

	sf::Music backgroundMusic;
	sf::Music singleClick;
	sf::Music click;

public:
	bool menuClose;
	bool gameStart;
	bool showInformation;
	bool showStandings;

private:
	//Text and font
	sf::Font font;
	float sizeText;
	sf::Text startText;
	sf::Text informationText;
	sf::Text standingsText;
	sf::Text quitText;

	//Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	void initText();
	void initText(sf::Text& text);
public:
	Menu();
	virtual ~Menu();
	
	void run(sf::RenderWindow* window);

	const bool isMenuClose() const;
	const bool isGameStart() const;
	const bool isShowInfo() const;

	const sf::FloatRect getStartBounds() const;
	const sf::FloatRect getInformationBounds() const;
	const sf::FloatRect getQuitBounds() const;

	void updateTextIfMouseIn(sf::Text& text);
	void updateMouse(sf::RenderWindow* window);
	void updateGUI(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
	void renderGUI(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);

	void restartGame();
};

