#pragma once
#ifndef _CharacterKoopa_H
#define _CharacterKoopa_H
#include<iostream>
#include<SDL.h>
#include<string>
#include"commons.h"
#include "Character.h"

class Texture2D;

class CharacterKoopa : public Character 
{
protected:

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_movementSpeed;

	

	FACING m_facing_direction;
	LevelMap* m_current_level_map;

	

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map,FACING start_facing,float movement_speed);
	~CharacterKoopa();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void FlipRightWayUp();
	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }
};

#endif // !_CharacterKoopa_H