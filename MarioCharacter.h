#pragma once
#ifndef _MarioCharacter_H
#define _MarioCharacter_H
#include<iostream>
#include<SDL.h>
#include<string>
#include"commons.h"
#include "Character.h"

class Texture2D;

class Character;

class MarioCharacter : public Character
{
protected:
	//SDL_Renderer* m_renderer;
	//Vector2D m_position;
	//Texture2D* m_texture;

	//bool m_moving_left;
	//bool m_moving_right;
	//bool m_jumping;
	//bool m_can_jump;
	//float m_jump_force;

	//void MoveLeft(float deltaTime);
	//void MoveRight(float deltaTime);
	//void Jumping();
private:
	FACING m_facing_direction;
	LevelMap* m_current_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;

	int m_current_frame;
	float m_frame_delay;

public:
	MarioCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~MarioCharacter();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	
	//void AddGravity(float deltaTime);
	//float GetCollisionRadius();
	//void setPosition(Vector2D new_position);
	//Vector2D getPosition();
};

#endif // !_MarioCharacter_H