#include "CharacterGoomba.h"
#include "Texture2D.h"
#include "constant.h"
#include"Character.h"
#include"LevelMap.h"
#include<iostream>

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, startPosition, map)
{
	m_current_frame = 0;
	m_frame_delay = ANIMATION_DELAY;
	m_current_level_map = map;
	m_facing_direction = start_facing;
	m_movementSpeed = movement_speed;
	m_position = startPosition;
	m_injured = false;
	m_alive = true;
	
	m_single_sprite_h = (m_texture->GetHeight() / 2);
	m_single_sprite_w = (m_texture->GetWidth() / 3);
}


void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	//Character::Update(deltaTime, e);

	

	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;
		m_current_frame++;

		if (m_current_frame > 1)
		{
			m_current_frame = 0;
		}
	}


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


	int centeralX_Position = (int)(m_position.x + (m_texture->GetWidth() * 0.33)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + (m_texture->GetHeight()*0.5)) / TILE_HEIGHT;
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
}

void CharacterGoomba::Render()
{
	int left = 0.0f;
	int up = 0.0f;

	

	SDL_Rect portion_of_sprite = { 0,m_single_sprite_h * m_current_frame,m_single_sprite_w,m_single_sprite_h};

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


void CharacterGoomba::FlipRightWayUp()
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

void CharacterGoomba::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();


}

void CharacterGoomba::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}

}

CharacterGoomba::~CharacterGoomba()
{

}
