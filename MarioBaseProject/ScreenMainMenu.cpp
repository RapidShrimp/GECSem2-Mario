#include "ScreenMainMenu.h"
#include "Constants.h"

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
	//Title
	SDL_Rect MenuPortion = { 0,0,240,96 };
	SDL_Rect MenuPosition = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT / 2 };
	m_background_texture->Render(MenuPortion, MenuPosition, SDL_FLIP_NONE);
	

	//Text
	 m_SingleplayerText->Render(125, SCREEN_HEIGHT/2 + 50);
	 m_MultiplayerText->Render(125, SCREEN_HEIGHT / 2 + 110);
	//Character Selector

	SDL_Rect SelectPortion = { 52,106,9,9 };
	SDL_Rect SelectPosition;
	if (IsPlayer1)
	{
		SelectPosition = { 80,SCREEN_HEIGHT / 2 + 58, 30,30};
	}
	else 
	{ 
		SelectPosition = { 80,SCREEN_HEIGHT / 2 + 118, 30,30 };
	}
	m_character_select->Render(SelectPortion, SelectPosition, SDL_FLIP_NONE);

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
	m_character_select = new Texture2D(m_renderer);
	if (!m_character_select->LoadFromFile("Images/SpriteSheet.png")) 
	{
		cout << "Failed to Load Character Selector" << endl;
		return false;
	}
	m_SingleplayerText = new TextRenderer(m_renderer);
	if (!m_SingleplayerText->LoadFont("Fonts/PixelFont.ttf", 34, "Singleplayer", { 255, 130, 10, 255 }))
	{
		cout << "Failed to Load Singleplayer Text Font" << endl;
		return false;
	}
	m_MultiplayerText = new TextRenderer(m_renderer);
	if (!m_MultiplayerText->LoadFont("Fonts/PixelFont.ttf", 34, "Multiplayer", { 255, 130, 10, 255 }))
	{
		cout << "Failed to Load Mutliplayer Text Font" << endl;
		return false;
	}
	return true;

}
