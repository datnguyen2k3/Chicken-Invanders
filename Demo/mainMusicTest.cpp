#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(1240, 620), "Test Animation");
	renderWindow.setFramerateLimit(60);
	sf::Event event;

	sf::Music music;
	music.openFromFile("Sounds/start_wav.wav");
	music.setVolume(50);

	sf::Clock clockMusicStart;
	music.play();
	music.setLoop(true);

	while (renderWindow.isOpen())
	{

		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}

		if (clockMusicStart.getElapsedTime().asSeconds() >= 45) {
			clockMusicStart.restart();
			music.setPosition(0, 0, 0);
		}




		renderWindow.clear();
		renderWindow.display();

	}

	return 0;
}