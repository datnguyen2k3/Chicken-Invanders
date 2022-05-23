#include "Menu.h"

void Menu::initText()
{
	this->sizeText = 50.f;

	if(!this->font.loadFromFile("Fonts/font1.ttf"))
		printf("NOT LOAD FONT START\n");

	this->startText.setFont(this->font);
	this->startText.setCharacterSize(this->sizeText);
	this->startText.setFillColor(sf::Color::White);
	this->startText.setString("START");

	this->informationText.setFont(this->font);
	this->informationText.setCharacterSize(this->sizeText);
	this->informationText.setFillColor(sf::Color::White);
	this->informationText.setString("INFORMATION");

	this->quitText.setFont(this->font);
	this->quitText.setCharacterSize(this->sizeText);
	this->quitText.setFillColor(sf::Color::White);
	this->quitText.setString("QUIT");

	this->standingsText.setFont(this->font);
	this->standingsText.setCharacterSize(this->sizeText);
	this->standingsText.setFillColor(sf::Color::White);
	this->standingsText.setString("STANDINGS");

	//Position text
	this->startText.setPosition(1600.f / 2 - this->startText.getCharacterSize() * 2.f, 500.f);
	this->informationText.setPosition(1600.f / 2 - this->informationText.getCharacterSize() * 4.f, 600.f);
	this->standingsText.setPosition(1600.f / 2 - this->startText.getCharacterSize() * 3.3f, 700.f);
	this->quitText.setPosition(1600.f / 2 - this->startText.getCharacterSize() * 1.55f, 800.f);
}

Menu::Menu()
{	
	//Background
	this->textureBackground.loadFromFile("Textures/background_menu.png");
	this->spriteBackground.setTexture(this->textureBackground);
	this->spriteBackground.setScale(16 / 12.f, 16 / 12.f);

	//Logo
	this->textureLogo.loadFromFile("Textures/logo.png");
	this->spriteLogo.setTexture(this->textureLogo);
	this->spriteLogo.scale(1500 / 1084.f, 1.f);
	this->spriteLogo.setPosition(50.f, 50.f);

	//Variables
	this->menuClose = false;
	this->gameStart = false;
	this->showInformation = false;
	this->showStandings = false;

	this->backgroundMusic.openFromFile("Sounds/start_wav.wav");
	this->backgroundMusic.setLoop(true);
	this->backgroundMusic.setPlayingOffset(sf::seconds(0));
	this->backgroundMusic.play();

	this->singleClick.openFromFile("Sounds/single_click.wav");
	this->click.openFromFile("Sounds/click.wav");

	this->initText();
}

Menu::~Menu()
{

}

void Menu::run(sf::RenderWindow* window)
{
	if (this->isMenuClose() == false) 
	{
		this->update(window);
		this->render(window);
	}
	
}

const bool Menu::isMenuClose() const
{
	return this->menuClose;
}

const bool Menu::isGameStart() const
{
	return this->gameStart;
}

const bool Menu::isShowInfo() const
{
	return this->showInformation;
}

const sf::FloatRect Menu::getStartBounds() const
{
	return this->startText.getGlobalBounds();
}

const sf::FloatRect Menu::getInformationBounds() const
{
	return this->informationText.getGlobalBounds();
}

const sf::FloatRect Menu::getQuitBounds() const
{
	return this->quitText.getGlobalBounds();
}




void Menu::updateMouse(sf::RenderWindow* window)
{
	this->mousePosWindow = sf::Mouse::getPosition(*window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void Menu::updateTextIfMouseIn(sf::Text& text)
{
	if (text.getGlobalBounds().contains(this->mousePosView))
	{
		if( text.getFillColor() != sf::Color::Red)
		{
			this->singleClick.setPlayingOffset(sf::seconds(0.11));
			this->singleClick.play();

			text.setFillColor(sf::Color::Red);
		}

	}
	else
		text.setFillColor(sf::Color::White);
}


void Menu::updateGUI(sf::RenderWindow* window)
{
	//set color if mouse in text
	this->updateTextIfMouseIn(this->startText);
	this->updateTextIfMouseIn(this->informationText);
	this->updateTextIfMouseIn(this->standingsText);
	this->updateTextIfMouseIn(this->quitText);

	//mouse click text
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->startText.getGlobalBounds().contains(this->mousePosView))
	{
		this->gameStart = true;
		this->menuClose = true;
		this->backgroundMusic.pause();
		this->click.setPlayingOffset(sf::seconds(0.2));
		this->click.play();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->informationText.getGlobalBounds().contains(this->mousePosView))
	{
		this->click.setPlayingOffset(sf::seconds(0.2));
		this->click.play();

		this->showInformation = true;
		this->menuClose = true;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->standingsText.getGlobalBounds().contains(this->mousePosView))
	{
		this->click.setPlayingOffset(sf::seconds(0.2));
		this->click.play();

		this->showStandings = true;
		this->menuClose = true;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->quitText.getGlobalBounds().contains(this->mousePosView))
	{
		this->click.setPlayingOffset(sf::seconds(0.2));
		this->click.play();
		window->close();
	}
}

void Menu::update(sf::RenderWindow* window)
{
	this->updateMouse(window);
	this->updateGUI(window);
}

void Menu::renderGUI(sf::RenderWindow* window)
{
	window->draw(this->startText);
	window->draw(this->informationText);
	window->draw(this->quitText);
	window->draw(this->standingsText);
}


void Menu::render(sf::RenderWindow* window)
{
	window->clear();

	window->draw(this->spriteBackground);
	window->draw(this->spriteLogo);
	this->renderGUI(window);

	window->display();
}

void Menu::restartGame()
{
}
