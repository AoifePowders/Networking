#include "Game.h"


Game::Game()
{
	m_exitGame = false;

	//Creates my Player
	m_circle = Dot(true);
	m_enemy = Dot(false);
	m_enemyTwo = Dot(false);
}


Game::~Game()
{
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen, Client myClient)
{
	int flags = 0;

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << " ERROR " << IMG_GetError() << std::endl;
	}

	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << " Subsystem initialised!!" << std::endl;
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		if (window)
		{
			std::cout << "Window Created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0 | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;

		}

		isRunning = true;

	}
	else
	{
		isRunning = false;
	}

	m_circle.Init(renderer);
	m_circle.SetPosition(100, 400);
	

	m_enemy.Init(renderer);

	m_enemyTwo.Init(renderer);

	//myClient.SendCircle(m_circle);
}

/// handle user and system events/ input
void Game::processEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_circle.handleEvent(event);
		m_enemy.handleEvent(event);
		m_enemyTwo.handleEvent(event);

	}
}


/// Update the game world
void Game::update(Client myClient)
{
	//if (!m_circle.Checkcollision(m_enemy.GetCenterX(), m_enemy.GetCenterY()))
	//{
		myClient.SendCircle(m_circle);
		if (!myClient.vec.empty())
		{
			m_enemy.SetPosition(myClient.vec.at(0), myClient.vec.at(1));
			//m_enemyTwo.SetPosition(myClient.vec.at(2), myClient.vec.at(3));
			myClient.vec.clear();
		}
		m_circle.aliveTime();
		m_circle.move(500, 700);


 //	}
	//else
	//{
	//	std::cout << m_circle.timeAlive << std::endl;
	//}
}

/// draw the frame and then switch bufers
void Game::render()
{
	//Clears image after every frame
	SDL_RenderClear(renderer);

	//Draw here
	m_circle.render(renderer);
	m_enemy.render(renderer);
	m_enemyTwo.render(renderer);

	//Presents the new Images
	SDL_RenderPresent(renderer);
}

void Game::cleanUp()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	
	window = nullptr;
	renderer = nullptr;

	SDL_Quit();
	std::cout << "Cleaned" << std::endl;

}


