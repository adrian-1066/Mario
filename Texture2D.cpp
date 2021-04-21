#include "Texture2D.h"
#include<SDL_image.h>
#include<iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;

}
Texture2D::~Texture2D()
{
	Free();
	m_renderer = nullptr;

}

bool Texture2D::LoadFromFile(std::string path)
{
	Free();
	m_texture = nullptr;
	//load the image

	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//create texture from pixels on surface
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr)
		{
			cout << "unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}

		//remove the loader surface now we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		cout << "unable to create texture from surface. Error:  " << IMG_GetError() << endl;
	}

	return m_texture != nullptr;

}
void Texture2D::Free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_height = 0.0f;
		m_width = 0.0f;
	}

}
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angel)
{
	//SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderClear(m_renderer);

	SDL_Rect renderLocation = { new_position.x,new_position.y,m_width,m_height };

	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, 0, nullptr, flip);

	//SDL_RenderPresent(m_renderer);
}

void Texture2D::Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angel)
{
	SDL_RenderCopyEx(m_renderer, m_texture, &src_rect, &src_dest, angel, nullptr, flip);

}
