#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "Constants.h"
#include <iostream>
using namespace std;

//GlobalVariables
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

//FunctionPrototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();


int main(int argc, char* args[])
{
	//check if sdl was setup correctly
	if (InitSDL())
	{
		bool quit = false;
		while (!quit)
		{
			Render();
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

		//Attach Renderer To Window
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer != nullptr) 
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags)) 
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError() << endl;
				return false;
			}
		}
		else 
		{
			cout << "SDL_Renderer Could not initialise. Error: " << SDL_GetError() << endl;
			return false;
		}
	}
	g_texture = LoadTextureFromFile("Images/test.bmp");
	if (g_texture == nullptr) 
	{
		cout << "Couldnt Load Image" << SDL_GetError()<< endl;
		return false;
	}

	return true;
}

void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	FreeTexture();
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

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

void Render()
{
	//Clear Screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);
	//Set Render Location
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//Render To Screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	//Update Screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
	//Remove Memory of Previous Texture
	FreeTexture();
	SDL_Texture* p_Texture = nullptr;

	//Load Image
	SDL_Surface* p_Surface = IMG_Load(path.c_str());
	if (p_Surface != nullptr) 
	{
		p_Texture = SDL_CreateTextureFromSurface(g_renderer, p_Surface);
		if (p_Texture == nullptr) 
		{
			cout << "Unable to Create Texture From Surface. Error:" << SDL_GetError() << endl;
		}
		SDL_FreeSurface(p_Surface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error:" << IMG_GetError() << endl;
	}
	return p_Texture;
}

void FreeTexture()
{
	if (g_texture != nullptr) {
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}
