#include<SFML/Graphics.hpp>
#include<iostream>

int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(1240, 620), "Test Animation");
	renderWindow.setFramerateLimit(60);
	sf::Event event;

	sf::Image image;
	image.loadFromFile("Textures/boss.png");
	image.createMaskFromColor(sf::Color(170, 170, 170));

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::IntRect rectSourceSprite(0, 0, texture.getSize().x / 10.f, texture.getSize().y);
	sf::Sprite sprite(texture, rectSourceSprite);
	sprite.setPosition(50.0f, 50.0f);

	sf::Clock clock;
	int time = 0;

	while (renderWindow.isOpen())
	{

		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}

		renderWindow.clear();

		sprite.move(0.1f, 0.1f);
		if (clock.getElapsedTime().asSeconds() > 0.05f)
		{
			if (rectSourceSprite.left == 2000 - 200) {
				rectSourceSprite.left = 0;
			}
			else {
				rectSourceSprite.left += 200;
			}
			std::cout << time << std::endl;
			time++;

			sprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}

		renderWindow.draw(sprite);
		renderWindow.display();

	}

	return 0;
}