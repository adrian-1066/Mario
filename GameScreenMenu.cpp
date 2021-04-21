#include "GameScreenMenu.h"
#include"Texture2D.h"
#include<iostream>

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpMenu();
}

GameScreenMenu::~GameScreenMenu()
{
	m_background_texture = nullptr;
}

void GameScreenMenu::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{

}

bool GameScreenMenu::SetUpMenu()
{
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/Start_Screen.png"))
	{
		std::cout << "failed to load menu texture!" << std::endl;
		return false;
	}

	return true;
}
