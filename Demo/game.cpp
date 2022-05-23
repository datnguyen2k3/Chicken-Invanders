#include "game.h"

//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Chicken Invaders" , sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(true);
}

void Game::initGUI()
{
	this->font.loadFromFile("Fonts/font1.ttf");
}

void Game::initSound()
{
	this->soundChickenHit1.openFromFile("Sounds/ChickenHit1.wav");
	this->soundChickenHit2.openFromFile("Sounds/ChickenHit2.wav");
	this->soundChickenHit3.openFromFile("Sounds/ChickenHit3.wav");
}

void Game::initGameLogic()
{
	this->gameStart = false;
	this->gamePause = false;
	this->gameWin = false;
	this->gameLose = false;
	this->gameEnd = false;

	this->pauseText.setFont(this->font);
	this->pauseText.setString("Press P to continue!");
	this->pauseText.setPosition(300, 300);
	this->pauseText.setCharacterSize(100);
	this->pauseText.setFillColor(sf::Color::Yellow);
}

void Game::initGamePlay()
{
	this->initGUI();
	this->initSound();
	this->initGameLogic();

	this->player = new Player();

	this->bullets = new ManyBullets();
	this->chickens = new ManyChickens();
	this->eggs = new ManyEgg();
	this->bulletPower = new BulletPower();
	this->boss = new Boss();
	this->eggBosses = new ManyEggBoss();
	this->board = new PointBoard();
	this->background = new Background();

	this->stangdings = new Standings();
}

//Constructors and Destructors
Game::Game()
{
	this->initWindow();
	this->menu = new Menu();
	this->info = new Information();
	this->initGamePlay();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->menu;
	delete this->info;

	delete this->bullets;
	delete this->chickens;
	delete this->eggs;
	delete this->bulletPower;
	delete this->boss;
	delete this->eggBosses;
	delete this->board;
	delete this->background;

}

//Functions
void Game::run()
{
	while (this->window->isOpen()) 
	{
		this->updatePollEvents();

		this->menu->run(this->window);

		if (this->menu->isShowInfo()) {
			this->info->open = true;
			this->info->run(this->window);
			this->menu->menuClose = this->info->isOpen();
			this->menu->showInformation = this->info->isOpen();
		}

		if (this->menu->showStandings) {
			this->stangdings->open = true;
			this->stangdings->run(this->window);
			this->menu->menuClose = this->stangdings->open;
			this->menu->showStandings = this->stangdings->open;
		}

		if (this->menu->isGameStart()) {
			this->board->start();
			this->runGameplay();
		}
	}


}

void Game::runGameplay()
{
	this->updateInput();
	if (this->gamePause == false) {
		this->updateGamePlay();
	}
	this->renderGamePlay();
	if (this->gameEnd == true) {
		this->board->endGame();
		//if(this->gameWin == true)
			this->stangdings->push(this->board->getTime());
		if (this->gameEndClock.getElapsedTime().asSeconds() > 5.f)
			this->restartGame();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && this->pauseClock.getElapsedTime().asSeconds() > 0.5f)
	{
		this->pauseClock.restart();
		if (this->gamePause == true) {
			this->board->continueGame();
			this->gamePause = false;
		}
		else {
			this->board->pauseGame();
			this->gamePause = true;
		}
	}
}

void Game::updateInputPlayer()
{
	//Add bullet
	this->bullets->addBullet(this->player);

	//Player out of window
	this->player->outOfWindow(this->window);
}

//Combat
void Game::updateChickenKilled()
{
	for (int i = 0; i < this->chickens->chickenList.size(); i++)
	{
		bool breakLoop = false;
		for (int j = 0; j < this->bullets->bulletList.size() && breakLoop == false; j++)
		{	
			if (this->chickens->chickenList[i]->getBounds().intersects(this->bullets->bulletList[j]->getBounds()))
			{
				delete this->bullets->bulletList[j];
				this->bullets->bulletList.erase(this->bullets->bulletList.begin() + j);

				this->soundChickenHit1.setPlayingOffset(sf::seconds(0));
				this->soundChickenHit1.play();

				this->chickens->chickenList[i]->getDamage(this->bullets->getDamage());
				if (this->chickens->chickenList[i]->getHp() <= 0)
				{
					this->soundChickenHit3.setPlayingOffset(sf::seconds(0));
					this->soundChickenHit3.play();

					delete this->chickens->chickenList[i];
					this->chickens->chickenList.erase(this->chickens->chickenList.begin() + i);
				}

				breakLoop = true;
			}
		}
	}

	if (this->chickens->chickenList.size() > 0)
		return;

	if (this->boss->isDead())
		return;

	for (int i = 0; i < this->bullets->bulletList.size(); i++)
	{
		if (this->bullets->bulletList[i]->getBounds().intersects(this->boss->getBounds()))
		{
			this->soundChickenHit2.setPlayingOffset(sf::seconds(0));
			this->soundChickenHit2.play();

			delete this->bullets->bulletList[i];
			this->bullets->bulletList.erase(this->bullets->bulletList.begin() + i);
			this->boss->getDamge(this->bullets->getDamage());

			return;
		}
	}

}

void Game::updatePlayerDead()
{
	//Killed by small chicken
	if (this->player->isDead())
	{
		if (this->player->getHp() > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			this->player->setPlayerIsLive();
			this->bullets->resetPowerBullet();
		}

		return;
	}

	for (int i = 0; i < this->chickens->chickenList.size(); i++)
	{
		if (this->player->getBounds().intersects(this->chickens->chickenList[i]->getBounds()))
		{
			this->player->setPlayerisDead();
			return;
		}
	}

	for (int i = 0; i < this->eggs->eggList.size(); i++)
	{
		if (this->player->getBounds().intersects(this->eggs->eggList[i]->getBounds()))
		{
			this->player->setPlayerisDead();
			return;
		}
	}

	//Killed by Boss
	if (chickens->chickenList.size() > 0)
		return;

	if (this->boss->isDead())
		return;

	if (this->boss->getBounds().intersects(this->player->getBounds()))
	{
		this->player->setPlayerisDead();
		return;
	}

	if (this->boss->isDead())
		return;

	for (auto* eggBoss : this->eggBosses->eggList)
	{
		if (eggBoss->getBounds().intersects(this->player->getBounds()))
		{
			this->player->setPlayerisDead();
			return;
		}
	}
}

void Game::updateCombat()
{
	this->updateAddEgg();
	this->updateChickenKilled();
	this->updatePlayerDead();
	this->updateBossKilled();
}

void Game::updateAddEgg()
{
	if (this->eggClock.getElapsedTime().asSeconds() > 1 && !this->chickens->chickenList.empty()) {

		int a = rand() % this->chickens->chickenList.size();
		this->eggs->addEgg(this->chickens->chickenList[a]->getPos().x,
						  this->chickens->chickenList[a]->getPos().y);
		this->eggClock.restart();
	}

	if (this->chickens->chickenList.size() > 0)
		return;


	if (this->eggBossClock.getElapsedTime().asSeconds() > 0.5 && this->boss->getHp() > 0)
	{
		this->eggBosses->addEgg(this->boss->getPos().x + this->boss->getSize().x / 20 * 1.5 - this->eggBosses->getSize().x / 2,
							   this->boss->getPos().y + this->boss->getSize().y * 1.5);
		this->eggBossClock.restart();
	}


}

void Game::updatePower()
{
	if(this->bulletPower->isExistBulletPower())
	{
		if (this->player->getBounds().intersects(this->bulletPower->getBounds()))
		{
			// update power
			this->bullets->updatePowerBullet();

			this->bulletPower->updateBulletPowerDead();
		}
		else if (this->bulletPower->getPos().y > this->window->getSize().y) {
			this->bulletPower->updateBulletPowerDead();
		}
	}
}

void Game::updateBossKilled()
{
	if (this->chickens->chickenList.size() > 0)
		return;

	if (this->boss->isDead())
		return;

	if (this->boss->getHp() <= 0) {
		this->boss->setBossDead();
		this->player->setPlayerWin();
		this->gameWin = true;
	}
}

void Game::checkGameEnd()
{
	if (this->gameEnd == true)
		return;

	if (this->player->getHp() <= 0) 
	{
		this->gameEnd = true;
		this->gameLose = true;
		this->gameEndClock.restart();
		this->player->setPlayerLose();
		return;
	}
	if (this->gameWin == true)
	{
		this->gameEnd = true;
		this->gameEndClock.restart();
	}
}

//GUI
void Game::updateGUI()
{

}

void Game::updateGamePlay()
{
	this->background->update();
	this->player->update();
	this->updateInputPlayer();
	this->bullets->update();
	this->bulletPower->update();
	this->updatePower();
	this->chickens->update();
	this->eggs->update();

	if (this->chickens->chickenList.size() == 0)
	{
		this->boss->update();
		this->eggBosses->update();
	}

	this->updateCombat();
	this->board->update(this->chickens->chickenDead(), this->bullets->getLevelBullet(), this->player->getHp());
	this->checkGameEnd();
}

void Game::renderGUI()
{
	this->window->draw(pointText);
}

void Game::renderGamePlay()
{
	this->window->clear();

	//Draw window
	this->background->render(this->window);
	this->bullets->render(this->window);
	this->player->render(this->window);
	this->bulletPower->render(this->window);
	this->chickens->render(this->window);
	this->eggs->render(this->window);

	if (this->chickens->chickenList.size() == 0)
	{
		this->boss->render(this->window);
		if(this->boss->isDead() == false)
			this->eggBosses->render(this->window);
	}
	this->board->render(this->window);

	if (this->gamePause == true)
		this->window->draw(this->pauseText);

	this->window->display();
}

void Game::restartGame()
{
	delete this->player;
	delete this->bullets;
	delete this->chickens;
	delete this->eggs;
	delete this->bulletPower;
	delete this->boss;
	delete this->eggBosses;
	delete this->board;
	delete this->background;
	delete this->menu;
	delete this->stangdings;
	this->player = new Player();
	this->bullets = new ManyBullets();
	this->chickens = new ManyChickens();
	this->eggs = new ManyEgg();
	this->bulletPower = new BulletPower();
	this->boss = new Boss();
	this->eggBosses = new ManyEggBoss();
	this->board = new PointBoard();
	this->background = new Background();
	this->menu = new Menu();
	this->stangdings = new Standings();

	this->initGameLogic();
}



