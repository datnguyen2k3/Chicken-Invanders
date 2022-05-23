#include "Standings.h"

void Standings::initText(sf::Text& text, std::string word, sf::Vector2f pos)
{
	text.setCharacterSize(70.f);
	text.setFillColor(sf::Color::White);
	text.setFont(this->font);
	text.setString(word);
	text.setPosition(pos);
}

Standings::Standings()
{
	this->textureBackground.loadFromFile("Textures/background_menu.png");
	this->spriteBackground.setTexture(this->textureBackground);
	this->spriteBackground.scale(16 / 12.f, 16 / 12.f);
	this->gameEnd = false;


	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
	this->initText(this->standingText, this->standingStr, sf::Vector2f(600, 100));
	this->standingText.setCharacterSize(100);
	this->initText(this->backText, "Back", sf::Vector2f(10, 10));

	this->singleClick.openFromFile("Sounds/single_click.wav");
	this->click.openFromFile("Sounds/click.wav");
}

Standings::~Standings()
{
}

void Standings::push(int time)
{
	if (this->gameEnd == true)
		return;

	this->gameEnd = true;

	std::ifstream in_standing_txt("standings.txt");
	std::vector<int> arrStanding = {time};
	int num;
	while (in_standing_txt >> num)
		arrStanding.push_back(num);
	sort(arrStanding.begin(), arrStanding.end());
	if (arrStanding.size() > this->SIZE_STANDINGS)
		arrStanding.pop_back();
	in_standing_txt.close();

	std::ofstream out_standing_txt("standings.txt");
	for (auto& num : arrStanding)
		out_standing_txt << num << " ";
	out_standing_txt.close();

}

void Standings::run(sf::RenderWindow* window)
{
	this->update(window);
	this->render(window);
}

const sf::FloatRect Standings::getBackBounds() const
{
	return this->backText.getGlobalBounds();
}

void Standings::updateMouse(sf::RenderWindow* window)
{
	this->mousePosWindow = sf::Mouse::getPosition(*window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void Standings::updateStandingStr()
{
	std::ifstream in_standing_txt("standings.txt");
	int index = 1, num = 0;
	this->standingStr.clear();
	this->standingStr = "Standings\n";
	while (in_standing_txt >> num) {
		this->standingStr += "    " + std::to_string(index++) + ". " + std::to_string(num) + "s" + "\n";
	}

	this->standingText.setString(this->standingStr);
	in_standing_txt.close();
}

void Standings::updateClick()
{
	if (this->backText.getGlobalBounds().contains(this->mousePosView))
	{
		if (this->backText.getFillColor() != sf::Color::Red)
		{
			this->backText.setFillColor(sf::Color::Red);
			this->singleClick.setPlayingOffset(sf::seconds(0.11));
			this->singleClick.play();
		}
	}
	else
		this->backText.setFillColor(sf::Color::White);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->backText.getGlobalBounds().contains(this->mousePosView))
	{
		this->open = false;
		this->click.setPlayingOffset(sf::seconds(0.2));
		this->click.play();
	}
}

void Standings::update(sf::RenderWindow* window)
{
	this->updateMouse(window);
	this->updateStandingStr();
	this->updateClick();
}

void Standings::render(sf::RenderWindow* window)
{
	window->clear();

	window->draw(this->spriteBackground);
	window->draw(this->standingText);
	window->draw(this->backText);

	window->display();
}
