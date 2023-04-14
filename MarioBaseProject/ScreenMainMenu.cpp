#include "ScreenMainMenu.h"

ScreenMainMenu::ScreenMainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetupMenu();
}

ScreenMainMenu::~ScreenMainMenu()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete m_renderer;
	m_renderer = nullptr;
}

void ScreenMainMenu::Render()
{
	m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}

bool ScreenMainMenu::SetupMenu()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;

}
