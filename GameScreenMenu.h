#pragma once
#ifndef _GameScreenMenu_H
#define _GameScreenMenu_H
#include"commons.h"
#include"GameScreen.h"
#include<SDL.h>

class Texture2D;

class GameScreenMenu : GameScreen
{
private:
	Texture2D* m_background_texture;
	bool SetUpMenu();

public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;


};

#endif // !_GameScreenMenu_H