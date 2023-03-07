#include "GameScreen.h"
using namespace std;

GameScreen::GameScreen(SDL_Renderer* renderer) { m_renderer = renderer; }
GameScreen::~GameScreen() { m_renderer = nullptr; }


void GameScreen::Update(float deltaTime, SDL_Event e)
{

}
void GameScreen::Render()
{
	
}