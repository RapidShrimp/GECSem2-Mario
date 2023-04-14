#include "ScreenMainMenu.h"

ScreenMainMenu::ScreenMainMenu(SDL_Renderer* renderer, GameScreenManager* manager) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_screen_manager = manager;
	SetupMenu();
}

ScreenMainMenu::~ScreenMainMenu()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete m_renderer;
	m_renderer = nullptr;
	delete m_screen_manager;
	m_screen_manager = nullptr;
}

void ScreenMainMenu::Render()
{
	m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}

void ScreenMainMenu::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			m_screen_manager->ChangeScreen(SCREEN_LEVEL1);
			break;
		}
	}
}

bool ScreenMainMenu::SetupMenu()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/SpriteSheet.png"))
	{
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;

}
