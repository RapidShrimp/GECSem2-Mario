#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "Constants.h"
#include <iostream>
using namespace std;

//GlobalVariables
SDL_Window* g_window = nullptr;

//FunctionPrototypes
bool InitSDL();
void CloseSDL();
bool Update();


int main(int argc, char* args[])
{
	//check if sdl was setup correctly
	if (InitSDL())
	{
		bool quit = false;
		while (!quit)
		{
			quit = Update();
		}
	}

	CloseSDL();
	return 0;

}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}
}

void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}

bool Update() 
{
	//Event Handler
	SDL_Event e;

	//Get Events
	SDL_PollEvent(&e);

	//Event Handle
	switch (e.type) 
	{
	case SDL_QUIT:
		return true;
		break;
	}
	return false;
}