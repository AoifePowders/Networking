#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Dot.h"
#include "Client.h"

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen,Client myClient);
	void update(Client myClient);

	void processEvents();
	void render();
	void cleanUp();

	bool running() { return isRunning; }

	Dot m_circle;
	Dot m_enemy;
	Dot m_enemyTwo;

private:
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	bool m_exitGame; // control exiting game

	SDL_Event event;
};

#endif // !GAME