#include "TextRenderer.h"
#include <iostream>

TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

TextRenderer::~TextRenderer()
{
	delete m_renderer;
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void TextRenderer::Render(int x, int y)
{
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &textRect);
}

bool TextRenderer::LoadFont(std::string filepath, int fontSize, const std::string Message, SDL_Color colour)
{
	m_font = TTF_OpenFont(filepath.c_str(), fontSize);
	if (!m_font)
	{
		std::cout << "Font not found" << TTF_GetError();
		return false;
	}
	SDL_Surface* text_surface;
	text_surface = TTF_RenderText_Solid(m_font, Message.c_str(), colour);
	if (!text_surface) 
	{
		std::cout << "SurfaceNotCreated";
		return false;
	}
	m_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
	if (!m_texture)
	{
		std::cout << "Texture not Created";
		return false;
	}
		TTF_CloseFont(m_font);
		SDL_FreeSurface(text_surface);
		SDL_QueryTexture(m_texture, nullptr, nullptr, &textRect.w, &textRect.h); 
		return m_texture;
	
}
