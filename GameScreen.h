#pragma once
#ifndef _GameScreen_H
#define _GameScreen_H

#include<SDL.h>

class GameScreen
{
protected:
	SDL_Renderer* m_renderer;

private:

public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);


};

#endif // !_GameScreen_H