#pragma once
#include<iostream>
#include<SDL.h>
#include<string>
#include"commons.h"
#include "Character.h"
#ifndef _CharacterCoin_H
#define _CharacterCoin_H

class Texture2D;

class CharacterCoin : public Character
{
protected:

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_collected;
	float m_injured_time;
	float m_movementSpeed;

	int m_current_frame;
	float m_frame_delay;


	FACING m_facing_direction;
	LevelMap* m_current_level_map;



public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterCoin();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	
	//void FlipRightWayUp();
	//void TakeDamage();
	//void Jump();
	bool GetCollected() { return m_collected; }
	void SetCollect(bool state) { m_collected = state; }
};

#endif // !_CharacterCoin_H