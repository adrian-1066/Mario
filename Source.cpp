#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include <iostream>


#include"constant.h"
#include"commons.h"
#include"Texture2D.h"
#include"GameScreenManager.h"

using namespace std;

SDL_Window* g_window = nullptr;

SDL_Renderer* g_renderer = nullptr;
//Texture2D* g_texture = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

Mix_Music* g_music = nullptr;
//int screen = SCREEN_MENU;

bool InitSDL();
void CLoseSDL();
bool Update();

void Render();
SDL_Texture* LoadTextureFromFile(string path);

void LoadMusic(string filePath);



int main(int argc, char* args[])
{
	bool quit = false;
	if (InitSDL())
	{
		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
		//set the time
		g_old_time = SDL_GetTicks();
		while (!quit)
		{
			Render();
			quit = Update();


		}



	}
	CLoseSDL();

	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initilize. Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		g_window = SDL_CreateWindow("games engine creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == nullptr)
		{
			cout << "window was not created. Error: " << SDL_GetError() << endl;
			return false;
		}
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);



		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image count not initilize. error: " << IMG_GetError() << endl;
				return false;
			}
		}
		else
		{
			cout << "renderer could not initilize. Error: " << SDL_GetError() << endl;
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "mixer could not init. Error: " << Mix_GetError() << endl;
			return false;
		}
		





		return true;


	}

}

void CLoseSDL()
{
	// release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// quit SDL subsystem
	IMG_Quit();
	SDL_Quit();

	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	delete game_screen_manager;
	game_screen_manager = nullptr;

	Mix_FreeMusic(g_music);
	g_music = nullptr;
	

}
int temp = 0;
bool Update()
{
	
	Uint32 new_time = SDL_GetTicks();
	SDL_Event e;
	// get events
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		/*case SDLK_f:
			cout << "f key pressed" << endl;
			return true;
			break;*/
		case SDLK_ESCAPE:
			cout << "escape key pressed" << endl;
			return true;
			break;

		case SDLK_1:
			
			cout << "1 pressed" << endl;
			if (temp == 0)
			{
				game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
				temp = 1 - temp;
			}
			else if (temp == 1)
			{
				game_screen_manager->ChangeScreen(SCREEN_MENU);
				temp = 1 - temp;
			}
			break;
		}


	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0, e);
	g_old_time = new_time;
	return false;

}

void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);
	game_screen_manager->Render();
	//g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	SDL_RenderPresent(g_renderer);
	

}

SDL_Texture* LoadTextureFromFile(string path)
{

	SDL_Texture* p_texture = nullptr;
	//load the image

	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//create texture from pixels on surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr)
		{
			cout << "unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}

		//remove the loader surface now we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "unable to create texture from surface. Error:  " << IMG_GetError() << endl;
	}

	return p_texture;

}

void LoadMusic(string filePath)
{
	g_music = Mix_LoadMUS(filePath.c_str());
	if (g_music == nullptr)
	{
		cout << "failed to load music. Error: " << Mix_GetError << endl;
	}

}