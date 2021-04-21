#include "CharacterKoopa.h"
#include "Texture2D.h"
#include "constant.h"
#include"Character.h"
#include"LevelMap.h"
#include<iostream>

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer,imagePath,startPosition,map)
{
	m_current_level_map = map;
	m_facing_direction = start_facing;
	m_movementSpeed = movement_speed;
	m_position = startPosition;
	m_injured = false;
	m_alive = true;
	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{

	Character::Update(deltaTime, e);
	if (!m_injured)
	{
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_left = false;
			m_moving_right = true;
		}
	}
	else
	{
		m_moving_right = false;
		m_moving_left = false;	
		m_injured_time -= deltaTime;
		if (m_injured_time <= 0.0f)
		{
			FlipRightWayUp();
		}
	}
}


void CharacterKoopa::Render()
{
	int left = 0.0f;

	if (m_injured)
	{
		left = m_single_sprite_w;
	}

	SDL_Rect portion_of_sprite = { left,0,m_single_sprite_w,m_single_sprite_h };

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

void CharacterKoopa::FlipRightWayUp()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_facing_direction = FACING_LEFT;
		m_position.x -= 1;
	}
	else if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
		m_position.x += 1;
	}
	m_injured = false;
	Jump();
}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();


}

void CharacterKoopa::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}

}
