#include "LuigiCharacter.h"
#include "Texture2D.h"
#include "constant.h"
#include"Character.h"
#include"LevelMap.h"
#include<iostream>


LuigiCharacter::LuigiCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition,map)
{
	m_collision_radius = 15.0f;
	m_renderer = renderer;
	m_position = startPosition;
	m_texture = new Texture2D(m_renderer);
	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;
	m_jumping = false;
	

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "failed to load character texture" << std::endl;
		
	}



}
LuigiCharacter::~LuigiCharacter()
{
	m_renderer = nullptr;
}

void LuigiCharacter::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
	else if (m_facing_direction == FACING_LEFT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
}


void LuigiCharacter::Update(float deltaTime, SDL_Event e)
{
	
	
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_j:
			std::cout << "j key pressed" << std::endl;
			m_moving_left = true;
			m_facing_direction = FACING_LEFT;
			break;
		case SDLK_l:
			std::cout << "l pressed" << std::endl;
			m_moving_right = true;
			m_facing_direction = FACING_RIGHT;
			break;

		case SDLK_i:

			if (m_can_jump)
			{
				std::cout << "i pressed" << std::endl;
				Jumping();
			}
			break;
		case SDLK_2:
			std::cout << getPosition().x << " " << getPosition().y  << std::endl;
	

		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_j:
			std::cout << "j key released" << std::endl;
			m_moving_left = false;
			break;
		case SDLK_l:
			std::cout << "l key released" << std::endl;
			m_moving_right = false;
			break;

		}
		break;

	}
	
	
	Character::Update(deltaTime, e);
	

}

