#pragma once
#ifndef _PowBlock_H
#define _PowBlock_H

#include<SDL.h>
#include"Texture2D.h"
#include"LevelMap.h"
#include"constant.h"
#include"commons.h"

class PowBlock
{

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;
public:
	PowBlock(SDL_Renderer* renderer,LevelMap* map);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
	void TakeHit();
	bool IsAvailiable() { return m_num_hits_left > 0; };

};

#endif // !_PowBlock_H