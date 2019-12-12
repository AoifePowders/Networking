#include <iostream>

#include "Client.h"


#include <iostream>
#include <SDL_image.h>
#include <SDL.h>

#include "Game.h"

using namespace std;

#define DEBUG_MSG

using namespace std;
int main(int argc, char* argv[])
{
	Client myClient("149.153.106.176", 1112); //Create client to localhost ("149.153.106.176") on port 1111


	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}
	else
	{
		DEBUG_MSG("Game Object Created");
		Game* game = new Game();


		//FrameRate Capping 
		const int Fps = 60;
		const int frameDelay = 1000 / Fps;

		Uint32 framestart;
		int frameTime;


		game->init("CircleNetworking", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false,myClient);


		while (game->running() == true)
		{

			framestart = SDL_GetTicks();

			game->processEvents();
			game->update(myClient);
			game->render();

			frameTime = SDL_GetTicks() - framestart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}


		game->cleanUp();
		return 0;
	}


	
}