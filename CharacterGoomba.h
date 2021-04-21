#pragma once
#ifndef _CharacterGoomba_H
#define _CharacterGoomba_H



#include<iostream>
#include<SDL.h>
#include<string>
#include"commons.h"
#include "Character.h"

class Texture2D;

class CharacterGoomba : public Character
{

protected:

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_movementSpeed;

	int m_current_frame;
	float m_frame_delay;

	FACING m_facing_direction;
	LevelMap* m_current_level_map;

public:
	CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterGoomba();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void FlipRightWayUp();
	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }
};

#endif // !_CharacterGoomba_H