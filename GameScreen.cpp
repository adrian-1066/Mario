#include "GameScreen.h"
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include <iostream>


#include"constant.h"
#include"commons.h"
#include"Texture2D.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;

}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render()
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{


}


