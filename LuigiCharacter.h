#pragma once
#ifndef _LuigiCharacter_H
#define _LuigiCharacter_H
#include<iostream>
#include<SDL.h>
#include<string>
#include"commons.h"
#include "Character.h"

class Texture2D;



class LuigiCharacter : public Character
{
protected:
	/*SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void Jumping();*/
private:
	FACING m_facing_direction;

public:
	LuigiCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~LuigiCharacter();
	//void Character::AddGravity(float deltaTime);
	void Render();
	void Update(float deltaTime, SDL_Event e);

	//void AddGravity(float deltaTime);
	//float GetCollisionRadius();
	//void setPosition(Vector2D new_position);
	//Vector2D getPosition();

};

#endif // !_LuigiCharacter_H