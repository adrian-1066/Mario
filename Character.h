#pragma once
#ifndef _Character_H
#define _Character_H

#include<iostream>
#include<SDL.h>
#include<string>
#include"LevelMap.h"
#include"commons.h"
#include "Texture2D.h"

class Texture2D;

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	float m_collision_radius;

	bool m_moving_left;
	bool m_moving_right;
	
	bool m_can_jump;
	float m_jump_force;

	bool m_alive;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jumping();
	

private:
	FACING m_facing_direction;
	LevelMap* m_current_level_map;


public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();
	bool m_jumping;
	void CancelJump() { m_jumping = false; }
	float GetCollisionRadius();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void AddGravity(float deltaTime);
	void coutStuff();
	void setPosition(Vector2D new_position);

	void SetAlive(bool isAlive) { m_alive = isAlive; }

	bool GetAlive() { return m_alive; }
	Vector2D getPosition();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
};

#endif // !_Character_H