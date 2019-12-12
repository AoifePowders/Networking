#include <iostream>
#include "Server.h"
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[])
{
	Server MyServer(1112, true); //Create server on port 100
	for (int i = 0; i < 3; i++) //Up to 100 times...
	{
		MyServer.ListenForNewConnection(); //Accept new connection (if someones trying to connect)
	}

	system("pause");
	return 0;
}