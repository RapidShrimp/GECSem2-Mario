#pragma once
#include <SDL_ttf.h>
#include <String>

class Texture2D;

class TextRenderer
{
public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();
	void Render(int x, int y);
	bool LoadFont(std::string filepath, int fontSize, const std::string Message, SDL_Color colour);
private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	mutable SDL_Rect textRect;
	TTF_Font* m_font;
};

