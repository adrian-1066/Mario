#include "Character.h"
#include "Texture2D.h"
#include "constant.h"
#include<iostream>

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	m_current_level_map = map;
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
		//return false;
	}

}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}

}
void Character::Update(float deltaTime, SDL_Event e)
{

	int centeralX_Position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
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

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			//m_current_level_map->ChangeTileAt(15, 12, 0);

			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					std::cout << m_current_level_map->GetTileAt(i,j) << " " ;
				}
				std::cout << std::endl;
			}
		}
	}

	
	

}
Vector2D Character::getPosition()
{
	return m_position;

}

void Character::setPosition(Vector2D new_position)
{
	m_position = new_position;

}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}

void Character::Jumping()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}

}
void Character::coutStuff()
{
	std::cout << "you called cout and its doing something" << std::endl;
}
void Character::AddGravity(float deltaTime)
{
	if (m_position.y + m_texture->GetHeight() <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
		m_can_jump = false;
	}
	else
	{
		m_can_jump = true;
	}

}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}