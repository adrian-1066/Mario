#include "MarioCharacter.h"
#include "Texture2D.h"
#include "constant.h"
#include<iostream>
//#include"Character.h"


MarioCharacter::MarioCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer,imagePath,startPosition,map)
{
	m_collision_radius = 15.0f;
	m_renderer = renderer;
	m_position = startPosition;
	m_current_level_map = map;
	m_texture = new Texture2D(m_renderer);
	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;
	m_jumping = false;
	m_alive = true;

	m_current_frame = 0;
	m_frame_delay = ANIMATION_DELAY;
	
	//m_can_jump = true;
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "failed to load character texture" << std::endl;
		//return false;
	}
	m_single_sprite_h = (m_texture->GetHeight() / 3);
	m_single_sprite_w = (m_texture->GetWidth() / 3);
	
	
}
MarioCharacter::~MarioCharacter()
{
	m_renderer = nullptr;
}

void MarioCharacter::Render()
{
	/*if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}*/

	SDL_Rect portion_of_sprite = { m_single_sprite_w,m_single_sprite_h,m_single_sprite_w,m_single_sprite_h };

	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y),m_single_sprite_w,m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}


void MarioCharacter::Update(float deltaTime, SDL_Event e)
{
	



	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			std::cout << "left arrow key pressed" << std::endl;
			m_moving_left = true;
			m_facing_direction = FACING_LEFT;
			break;
		case SDLK_RIGHT:
			std::cout << "right arrow pressed" << std::endl;
			m_moving_right = true;
			m_facing_direction = FACING_RIGHT;
			break;

		case SDLK_UP:

			if (m_can_jump)
			{
				std::cout << "up arrow pressed" << std::endl;
				Jumping();
			}
			break;

		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			std::cout << "left arrow key released" << std::endl;
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			std::cout << "right arrow key released" << std::endl;
			m_moving_right = false;
			break;

		}
		break;

	}
	
	int centeralX_Position = (int)(m_position.x + (m_texture->GetWidth()/ 3)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + (m_texture->GetHeight()/ 3)) / TILE_HEIGHT;
	if (m_current_level_map->GetTileAt(foot_position, centeralX_Position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		m_can_jump = true;
	}



	if (m_jumping)
	{
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}
	//AddGravity(deltaTime);

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
	//Character::Update(deltaTime,e);
	

}


